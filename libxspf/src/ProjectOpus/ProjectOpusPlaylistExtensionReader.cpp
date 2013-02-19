/*
 * libxspf - XSPF playlist handling library
 *
 * Copyright (C) 2006-2008, Sebastian Pipping / Xiph.Org Foundation
 * All rights reserved.
 *
 * Redistribution  and use in source and binary forms, with or without
 * modification,  are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions   of  source  code  must  retain  the   above
 *       copyright  notice, this list of conditions and the  following
 *       disclaimer.
 *
 *     * Redistributions  in  binary  form must  reproduce  the  above
 *       copyright  notice, this list of conditions and the  following
 *       disclaimer   in  the  documentation  and/or  other  materials
 *       provided with the distribution.
 *
 *     * Neither  the name of the Xiph.Org Foundation nor the names of
 *       its  contributors may be used to endorse or promote  products
 *       derived  from  this software without specific  prior  written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT  NOT
 * LIMITED  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS
 * FOR  A  PARTICULAR  PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL  THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL,    SPECIAL,   EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
 * (INCLUDING,  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Sebastian Pipping, sping@xiph.org
 */

/**
 * @file ProjectOpusPlaylistExtensionReader.cpp
 * Implementation of ProjectOpusPlaylistExtensionReader.
 */

#include <xspf/ProjectOpus/ProjectOpusPlaylistExtensionReader.h>
#include <xspf/ProjectOpus/ProjectOpusPlaylistExtension.h>
#include <xspf/XspfReader.h>
#include <xspf/XspfStack.h>
#include <xspf/XspfToolbox.h>
#include <cstdio>
#include <cstring>


/// @cond DOXYGEN_INGORE
#define PROJECT_OPUS_TEXT_ZERO_ATTRIBUTE_OUT_OF_SET(attr, set) _PT("Attribute '") attr _PT("' must be in ") set _PT(".")
/// @endcond


namespace Xspf {
namespace ProjectOpus {


/**
 * Holds tag types that are pushed on the readers's tag stack.
 */
enum ProjectOpusTag {
	TAG_OPUS_PROJECT_INFO = TAG_USER ///< po:info tag
};


/// @cond DOXYGEN_NON_API

/**
 * D object for ProjectOpusPlaylistExtensionReader.
 */
class ProjectOpusPlaylistExtensionReaderPrivate {

	friend class ProjectOpusPlaylistExtensionReader;

	ProjectOpusPlaylistExtension extension; ///< Extension being built
	bool firstInfo; ///< First info element flag

	/**
	 * Creates a new D object.
	 */
	ProjectOpusPlaylistExtensionReaderPrivate()
			: extension(), firstInfo(true) {

	}

	/**
	 * Destroys this D object.
	 */
	~ProjectOpusPlaylistExtensionReaderPrivate() {

	}

};

/// @endcond


ProjectOpusPlaylistExtensionReader::ProjectOpusPlaylistExtensionReader(
		XspfReader * reader)
		: XspfExtensionReader(reader),
		d(new ProjectOpusPlaylistExtensionReaderPrivate()) {

}


ProjectOpusPlaylistExtensionReader::ProjectOpusPlaylistExtensionReader(ProjectOpusPlaylistExtensionReader const & source)
		: XspfExtensionReader(source),
		d(new ProjectOpusPlaylistExtensionReaderPrivate(*(source.d))) {

}


ProjectOpusPlaylistExtensionReader & ProjectOpusPlaylistExtensionReader::operator=(ProjectOpusPlaylistExtensionReader const & source) {
	if (this != &source) {
		XspfExtensionReader::operator=(source);
		*(this->d) = *(source.d);
	}
	return *this;
}


ProjectOpusPlaylistExtensionReader::~ProjectOpusPlaylistExtensionReader() {
	delete this->d;
}


bool ProjectOpusPlaylistExtensionReader::handleExtensionStart(XML_Char const * fullName,
		XML_Char const ** atts) {
	switch (this->getElementStack().size() + 1) {
	case 2:
		// We only get called on this level for playlist.extension
		// Name and attributes have already been checked.
		this->getElementStack().push(TAG_PLAYLIST_EXTENSION);
		return true;

	case 3:
		// Check and skip namespace
		if (::PORT_STRNCMP(fullName, PROJECT_OPUS_NS_HOME, PROJECT_OPUS_NS_HOME_LEN)
				|| ::PORT_STRCMP(fullName + PROJECT_OPUS_NS_HOME_LEN + 1, _PT("info"))) {
			handleError(XSPF_READER_ERROR_ELEMENT_FORBIDDEN,
					XSPF_READER_TEXT_ONE_ELEMENT_FORBIDDEN,
					fullName);
			return false;
		}

		// One info at most
		if (!this->d->firstInfo) {
			handleError(XSPF_READER_ERROR_ELEMENT_TOOMANY,
					XSPF_READER_TEXT_ZERO_TOO_MANY_ELEMENTS(PROJECT_OPUS_NS_HOME, _PT("info")));
			return false;
		}

		if (!handleInfoAttribs(atts)) {
			return false;
		}

		this->d->firstInfo = false;
		this->getElementStack().push(TAG_OPUS_PROJECT_INFO);
		return true;

	case 4:
		if (this->getElementStack().top() == TAG_PLAYLIST_TRACKLIST_TRACK) {
			// Name and attributes have already been checked.
			this->getElementStack().push(TAG_PLAYLIST_TRACKLIST_TRACK_EXTENSION);
			return true;
		}
		break;

	}

	this->getElementStack().push(TAG_UNKNOWN);
	return true;
}


bool ProjectOpusPlaylistExtensionReader::handleExtensionEnd(XML_Char const * /*fullName*/) {
	switch (this->getElementStack().size()) {
	case 2:
		// One info minimum
		if (this->d->firstInfo) {
			handleError(XSPF_READER_ERROR_ELEMENT_MISSING,
					XSPF_READER_TEXT_ZERO_ELEMENT_MISSING(PROJECT_OPUS_NS_HOME, _PT("info")));
			return false;
		}
		break;

	}

	this->getElementStack().pop();
	return true;
}


bool ProjectOpusPlaylistExtensionReader::handleExtensionCharacters(XML_Char const * /*s*/, int /*len*/) {
	return true;
}


XspfExtension * ProjectOpusPlaylistExtensionReader::wrap() {
	return this->d->extension.clone();
}


XspfExtensionReader * ProjectOpusPlaylistExtensionReader::createBrother(XspfReader * reader) const {
	return new ProjectOpusPlaylistExtensionReader(reader);
}


bool ProjectOpusPlaylistExtensionReader::handleInfoAttribs(XML_Char const ** atts) {
	bool typeFound = false;
	bool nidFound = false;

	for (int i = 0; atts[i] != NULL; i += 2) {
		if (!::PORT_STRCMP(atts[i], _PT("type"))) {
			ProjectOpusPlaylistType dummyType = TYPE_PLAYLIST; // Init not needed
			if (!::PORT_STRCMP(atts[i], _PT("album"))) {
				dummyType = TYPE_ALBUM;
			} else if (!::PORT_STRCMP(atts[i + 1], _PT("playlist"))) {
				dummyType = TYPE_PLAYLIST;
			} else {
				handleError(XSPF_READER_ERROR_ATTRIBUTE_INVALID,
						PROJECT_OPUS_TEXT_ZERO_ATTRIBUTE_OUT_OF_SET(_PT("type"), _PT("{'album', 'playlist'}")));
				return false;
			}
			this->d->extension.setType(dummyType);
			typeFound = true;
		} else if (!::PORT_STRCMP(atts[i], _PT("nid"))) {
			int dummyNid;
			if (!Toolbox::extractInteger(atts[i + 1], 0, &dummyNid)) {
				handleError(XSPF_READER_ERROR_ATTRIBUTE_INVALID,
						XSPF_READER_TEXT_ZERO_WRONG_ATTRIBUTE_TYPE(_PT("nid"), _PT("unsigned integer")));
				return false;
			}
			this->d->extension.setNodeId(dummyNid);
			nidFound = true;
		} else if (XspfReader::isXmlBase(atts[i])) {
			// xml:base
			XML_Char const * const xmlBase = atts[i + 1];
			if (!handleXmlBaseAttribute(xmlBase)) {
				return false;
			}
		} else {
			handleError(XSPF_READER_ERROR_ATTRIBUTE_FORBIDDEN,
					XSPF_READER_TEXT_ONE_ATTRIBUTE_FORBIDDEN, atts[i]);
			return false;
		}
	}

	if (!typeFound) {
		handleError(XSPF_READER_ERROR_ATTRIBUTE_MISSING,
				XSPF_READER_TEXT_ZERO_ATTRIBUTE_MISSING(_PT("type")));
		return false;
	}

	if (!nidFound) {
		handleError(XSPF_READER_ERROR_ATTRIBUTE_MISSING,
				XSPF_READER_TEXT_ZERO_ATTRIBUTE_MISSING(_PT("nid")));
		return false;
	}

	return true;
}


}
}
