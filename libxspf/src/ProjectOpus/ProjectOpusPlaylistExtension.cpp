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
 * @file ProjectOpusPlaylistExtension.cpp
 * Implementation of ProjectOpusPlaylistExtension.
 */

#include <xspf/ProjectOpus/ProjectOpusPlaylistExtension.h>
#include <xspf/ProjectOpus/ProjectOpusPlaylistExtensionWriter.h>
#include <stdio.h>

namespace Xspf {
namespace ProjectOpus {


/*static*/ XML_Char const * const ProjectOpusPlaylistExtension
		::namespaceKey = PROJECT_OPUS_NS_HOME;


/*static*/ XML_Char const * const ProjectOpusPlaylistExtension
		::applicationURI = _PT("http://www.projectopus.com");


/// @cond DOXYGEN_NON_API

/**
 * D object for ProjectOpusPlaylistExtension.
 */
class ProjectOpusPlaylistExtensionPrivate {

	friend class ProjectOpusPlaylistExtension;

	ProjectOpusPlaylistType type; ///< Playlist type
	unsigned int nodeId; ///< Node ID

	/**
	 * Creates a new D object.
	 */
	ProjectOpusPlaylistExtensionPrivate()
			: type(TYPE_PLAYLIST),
			nodeId(0) {

	}

	/**
	 * Destroys this D object.
	 */
	~ProjectOpusPlaylistExtensionPrivate() {

	}

};

/// @endcond


ProjectOpusPlaylistExtension::ProjectOpusPlaylistExtension()
		: XspfExtension(ProjectOpusPlaylistExtension::namespaceKey),
		d(new ProjectOpusPlaylistExtensionPrivate()) {

}


ProjectOpusPlaylistExtension::ProjectOpusPlaylistExtension(ProjectOpusPlaylistExtension const & source)
		: XspfExtension(source),
		d(new ProjectOpusPlaylistExtensionPrivate(*(source.d))) {

}


ProjectOpusPlaylistExtension & ProjectOpusPlaylistExtension::operator=(ProjectOpusPlaylistExtension const & source) {
	if (this != &source) {
		XspfExtension::operator=(source);
		*(this->d) = *(source.d);
	}
	return *this;
}


ProjectOpusPlaylistExtension::~ProjectOpusPlaylistExtension() {
	delete this->d;
}


ProjectOpusPlaylistType ProjectOpusPlaylistExtension::getType() const {
	return this->d->type;
}


unsigned int ProjectOpusPlaylistExtension::getNodeId() const {
	return this->d->nodeId;
}


void ProjectOpusPlaylistExtension::setType(ProjectOpusPlaylistType type) {
	this->d->type = type;
}


void ProjectOpusPlaylistExtension::setNodeId(unsigned int nodeId) {
	this->d->nodeId = nodeId;
}


XspfExtension * ProjectOpusPlaylistExtension::clone() const {
	ProjectOpusPlaylistExtension * const clone
			= new ProjectOpusPlaylistExtension();
	clone->d->nodeId = this->d->nodeId;
	clone->d->type = this->d->type;
	return clone;
}


XspfExtensionWriter *
ProjectOpusPlaylistExtension::newWriter(XspfXmlFormatter * output,
		XML_Char const * baseUri) const {
	return new ProjectOpusPlaylistExtensionWriter(this, output, baseUri);
}


/*static*/ XML_Char const * ProjectOpusPlaylistExtension::typeToString(
		ProjectOpusPlaylistType type) {
	switch (type) {
	case TYPE_ALBUM:
		return _PT("album");

	default:
		return _PT("playlist");
	}
}


/*static*/ XML_Char * ProjectOpusPlaylistExtension::nodeIdToString(
		unsigned int nodeId) {
	size_t const charCount = 20;
	XML_Char * nodeIdText = new XML_Char[charCount];
	::PORT_SNPRINTF(nodeIdText, charCount, _PT("%d"), nodeId);
	return nodeIdText;
}


}
}
