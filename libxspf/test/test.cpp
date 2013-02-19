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

#include <cpptest.h>

#include "ChunkCallbackSuite.h"
#include "DateTimeSuite.h"
#include "ExtensionReaderFactorySuite.h"
#include "MaliciousXmlSuite.h"
#include "MemoryModelSuite.h"
#include "OfficialSuite.h"
#include "ReadWriteSuite.h"
#include "WhiteSpaceSuite.h"
#include "ProjectOpus/ProjectOpusSuite.h"

#include <memory>
using namespace Test;


int
PORT_MAIN() {
	// Combine all suites to one
	Suite suite;
	suite.add(std::auto_ptr<Suite>(new ChunkCallbackSuite()));
	suite.add(std::auto_ptr<Suite>(new DateTimeSuite()));
	suite.add(std::auto_ptr<Suite>(new ExtensionReaderFactorySuite()));
	suite.add(std::auto_ptr<Suite>(new MemoryModelSuite()));
	suite.add(std::auto_ptr<Suite>(new MaliciousXmlSuite()));
	suite.add(std::auto_ptr<Suite>(new OfficialSuite()));
	suite.add(std::auto_ptr<Suite>(new ReadWriteSuite()));
	suite.add(std::auto_ptr<Suite>(new WhiteSpaceSuite()));

	suite.add(std::auto_ptr<Suite>(new ProjectOpusSuite()));

	TextOutput output(TextOutput::Verbose);
	return suite.run(output, false) ? 0 : 1;
}
