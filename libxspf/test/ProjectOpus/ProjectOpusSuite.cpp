/*
 * libxspf - XSPF playlist handling library
 *
 * Copyright (C) 2006-2008, Sebastian Pipping / Xiph.Org Foundation
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Sebastian Pipping, sping@xiph.org
 */

#include "ProjectOpusSuite.h"
#include <xspf/XspfReader.h>
#include <xspf/XspfTrack.h>
#include <xspf/XspfProps.h>
#include <xspf/XspfExtensionReaderFactory.h>
#include <xspf/ProjectOpus/ProjectOpusPlaylistExtension.h>
#include <xspf/ProjectOpus/ProjectOpusPlaylistExtensionReader.h>
using namespace Xspf;
using namespace Xspf::ProjectOpus;


#undef SEP
#if (defined(__WIN32__) || defined(WIN32))
# define SEP _PT("\\")
#else
# define SEP _PT("/")
#endif

#ifndef XSPF_SRCDIR
# define XSPF_SRCDIR "."
#endif


ProjectOpusSuite::ProjectOpusSuite()
		: firstErrorText(), firstErrorLine(-1) {
	TEST_ADD(ProjectOpusSuite::parse_example)
}


void ProjectOpusSuite::addTrack(XspfTrack * track) {
	delete track;
}


void ProjectOpusSuite::setProps(XspfProps * props) {
	// Exactly one extension?
	TEST_ASSERT(props->getExtensionCount() == 1);
	ProjectOpusPlaylistExtension * const extension
			= static_cast<ProjectOpusPlaylistExtension *>(
			props->stealFirstExtension());

	// Test extension members
	TEST_ASSERT(extension->getNodeId() == 10197);
	TEST_ASSERT(extension->getType() == TYPE_PLAYLIST);
	delete props;
}


void
ProjectOpusSuite::runCase(XML_Char const * filename, XspfReader & reader,
		int expectedCode) {
	int const res = reader.parseFile(filename, this,
			_PT("http://www.example.org/"));

	if (res != expectedCode) {
		PORT_PRINTF(
				_PT("      File : %s\n")
				_PT("      Line : %i\n")
				_PT("Error text : '%s'\n")
				_PT("Error code : %i\n")
				_PT("  Expected : %i\n\n"),
				filename, this->firstErrorLine,
				this->firstErrorText.c_str(), res, expectedCode);
	}

	TEST_ASSERT(res == expectedCode);
}


void ProjectOpusSuite::parse_example() {
	// The factory will create extension readers
	// when the main reader stumbles over an extension
	XspfExtensionReaderFactory extensionReaderFactory;
	XspfReader reader(&extensionReaderFactory);

	// But before that the reader has to be registered.
	ProjectOpusPlaylistExtensionReader opusPlayistReader(&reader);
	extensionReaderFactory.registerPlaylistExtensionReader(
			&opusPlayistReader,
			ProjectOpusPlaylistExtension::applicationURI);

	// The callback receives tracks and playlist props
	// as they become available. The callback handler
	// in this case is this class
	runCase(_PT(XSPF_SRCDIR) SEP _PT("test") SEP _PT("ProjectOpus") SEP _PT("Example.xspf"), reader,
				XSPF_READER_SUCCESS);
}


bool 
ProjectOpusSuite::handleError(int line, int column, int errorCode,
		XML_Char const * description) {
	this->firstErrorLine = line;
	this->firstErrorText.assign(description);
	return false;
}
