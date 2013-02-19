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

#include "ExtensionReaderFactorySuite.h"
#include "../src/XspfSkipExtensionReader.h"
#include <xspf/XspfReader.h>
#include <xspf/XspfExtensionReaderFactory.h>
#include <xspf/XspfExtensionReader.h>
using namespace Xspf;


ExtensionReaderFactorySuite::ExtensionReaderFactorySuite() {
	TEST_ADD(ExtensionReaderFactorySuite::test_register_uri)
	TEST_ADD(ExtensionReaderFactorySuite::test_register_catch_all)
}


void ExtensionReaderFactorySuite::test_register_helper(XML_Char const * testUri) {
	XspfReader reader;
	XspfSkipExtensionReader skipExtensionReader(&reader);
	XspfExtensionReaderFactory factory;
	XspfExtensionReader * res;

	res = factory.newPlaylistExtensionReader(testUri, &reader);
	TEST_ASSERT(res == NULL);

	factory.registerPlaylistExtensionReader(&skipExtensionReader, testUri);
	res = factory.newPlaylistExtensionReader(testUri, &reader);
	TEST_ASSERT(res != NULL);
	delete res;

	factory.unregisterPlaylistExtensionReader(testUri);
	res = factory.newPlaylistExtensionReader(testUri, &reader);
	TEST_ASSERT(res == NULL);
}


void ExtensionReaderFactorySuite::test_register_uri() {
	test_register_helper(_PT("http://example.com/"));
}


void ExtensionReaderFactorySuite::test_register_catch_all() {
	test_register_helper(NULL);
}
