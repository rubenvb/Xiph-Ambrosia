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

#include "WhiteSpaceSuite.h"
#include <xspf/XspfToolbox.h>
using namespace Xspf;


#define WHITE_SPACE_ALL_WHITE_TEST(_input, inputLen, result) \
		{ \
		XML_Char const * const input = _input; \
		TEST_ASSERT(Toolbox::isWhiteSpace(input, inputLen) == result); \
		}

#define WHITE_SPACE_CUT_OFF_TEST(_input, inputLen, expectedOffset, expectedLen) \
		{ \
		XML_Char const * const input = _input; \
		XML_Char const * blackSpaceStart = NULL; \
		int blackSpaceNumChars = 0; \
		Toolbox::cutOffWhiteSpace(input, inputLen, blackSpaceStart, blackSpaceNumChars); \
		TEST_ASSERT(expectedOffset == blackSpaceStart - input); \
		TEST_ASSERT(blackSpaceNumChars == expectedLen); \
		}


WhiteSpaceSuite::WhiteSpaceSuite() {
	TEST_ADD(WhiteSpaceSuite::allWhiteWhite)
	TEST_ADD(WhiteSpaceSuite::allWhiteBlack)
	TEST_ADD(WhiteSpaceSuite::allWhiteMixed)

	TEST_ADD(WhiteSpaceSuite::cutOffHeadOne)
	TEST_ADD(WhiteSpaceSuite::cutOffHeadTwo)
	TEST_ADD(WhiteSpaceSuite::cutOffTailOne)
	TEST_ADD(WhiteSpaceSuite::cutOffTailTwo)
	TEST_ADD(WhiteSpaceSuite::cutOffMidOne)
	TEST_ADD(WhiteSpaceSuite::cutOffMidTwo)
	TEST_ADD(WhiteSpaceSuite::cutOffZero)
	TEST_ADD(WhiteSpaceSuite::cutOffNonSpace)
}


void WhiteSpaceSuite::allWhiteWhite() {
	WHITE_SPACE_ALL_WHITE_TEST(_PT(" \x0d\x0a\t"), 4, true)
}


void WhiteSpaceSuite::allWhiteBlack() {
	WHITE_SPACE_ALL_WHITE_TEST(_PT("X"), 1, false)
}


void WhiteSpaceSuite::allWhiteMixed() {
	WHITE_SPACE_ALL_WHITE_TEST(_PT("  X  "), 5, false)
}


void WhiteSpaceSuite::cutOffHeadOne() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("  X"), 3, 2, 1)
}


void WhiteSpaceSuite::cutOffHeadTwo() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("  X X"), 5, 2, 3)
}


void WhiteSpaceSuite::cutOffTailOne() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("X  "), 3, 0, 1)
}


void WhiteSpaceSuite::cutOffTailTwo() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("X X  "), 5, 0, 3)
}


void WhiteSpaceSuite::cutOffMidOne() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("  X  "), 5, 2, 1)
}


void WhiteSpaceSuite::cutOffMidTwo() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("  X X  "), 7, 2, 3)
}


void WhiteSpaceSuite::cutOffZero() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("X"), 1, 0, 1)
}


void WhiteSpaceSuite::cutOffNonSpace() {
	WHITE_SPACE_CUT_OFF_TEST(_PT("\t\tX\t\t"), 5, 2, 1)
	WHITE_SPACE_CUT_OFF_TEST(_PT("\x0a\x0aX\x0a\x0a"), 5, 2, 1)
	WHITE_SPACE_CUT_OFF_TEST(_PT("\x0d\x0dX\x0d\x0d"), 5, 2, 1)
}

