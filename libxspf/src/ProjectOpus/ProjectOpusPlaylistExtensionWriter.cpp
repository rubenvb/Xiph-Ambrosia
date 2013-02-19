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
 * @file ProjectOpusPlaylistExtensionWriter.cpp
 * Implementation of ProjectOpusPlaylistExtensionWriter.
 */

#include <xspf/ProjectOpus/ProjectOpusPlaylistExtensionWriter.h>
#include <xspf/ProjectOpus/ProjectOpusPlaylistExtension.h>
#include <xspf/XspfXmlFormatter.h>

namespace Xspf {
namespace ProjectOpus {


/// @cond DOXYGEN_NON_API

/**
 * D object for ProjectOpusPlaylistExtensionWriter.
 */
class ProjectOpusPlaylistExtensionWriterPrivate {

	friend class ProjectOpusPlaylistExtensionWriter;

	ProjectOpusPlaylistExtension const * opusExtension; ///< Extension to write

	/**
	 * Creates a new D object.
	 *
 	 * @param extension  Extension to write
	 */
	ProjectOpusPlaylistExtensionWriterPrivate(
			ProjectOpusPlaylistExtension const * extension)
			: opusExtension(extension) {

	}

	/**
	 * Destroys this D object.
	 */
	~ProjectOpusPlaylistExtensionWriterPrivate() {

	}

};

/// @endcond


ProjectOpusPlaylistExtensionWriter::ProjectOpusPlaylistExtensionWriter(
		ProjectOpusPlaylistExtension const * extension,
		XspfXmlFormatter * output, XML_Char const * baseUri)
		: XspfExtensionWriter(extension, output, baseUri),
		d(new ProjectOpusPlaylistExtensionWriterPrivate(extension)) {

}


ProjectOpusPlaylistExtensionWriter::ProjectOpusPlaylistExtensionWriter(ProjectOpusPlaylistExtensionWriter const & source)
		: XspfExtensionWriter(source),
		d(new ProjectOpusPlaylistExtensionWriterPrivate(*(source.d))) {

}


ProjectOpusPlaylistExtensionWriter & ProjectOpusPlaylistExtensionWriter::operator=(ProjectOpusPlaylistExtensionWriter const & source) {
	if (this != &source) {
		XspfExtensionWriter::operator=(source);
		*(this->d) = *(source.d);
	}
	return *this;
}


ProjectOpusPlaylistExtensionWriter::~ProjectOpusPlaylistExtensionWriter() {
	delete this->d;
}


void ProjectOpusPlaylistExtensionWriter::writeExtensionBody() {
	// Get type
	ProjectOpusPlaylistType const type = this->d->opusExtension->getType();
	XML_Char const * const typeText
			= ProjectOpusPlaylistExtension::typeToString(type);

	// Get node id
	unsigned int nodeId = this->d->opusExtension->getNodeId();
	XML_Char * const nodeIdText
			= ProjectOpusPlaylistExtension::nodeIdToString(nodeId);

	// Write <po:info>
	XML_Char const * atts[5] = {
			_PT("type"), typeText,
			_PT("nid"), nodeIdText,
			NULL};
	this->getOutput()->writeStart(
			ProjectOpusPlaylistExtension::namespaceKey,
			_PT("info"),
			atts);
	this->getOutput()->writeEnd(
			ProjectOpusPlaylistExtension::namespaceKey,
			_PT("info"));

	// Cleanup
	delete [] nodeIdText;
}


XML_Char const * const *
ProjectOpusPlaylistExtensionWriter::getNamespaceRegs() const {
	// Note "static"!
	static XML_Char const * nsRegs[3] = {
			ProjectOpusPlaylistExtension::namespaceKey,
			_PT("po"), // Recommendation only!
			NULL};
	return nsRegs;
}


}
}
