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

#include "MemoryModelSuite.h"
#include <xspf/XspfTrack.h>
#include <xspf/XspfToolbox.h>
using namespace Xspf;


MemoryModelSuite::MemoryModelSuite() {
	TEST_ADD(MemoryModelSuite::testOwnership);
}


void MemoryModelSuite::testOwnership() {
	XML_Char const * const text = _PT("abc");

	int i = 0;
	for (; i < 3; i++) {
		XspfTrack * track = new XspfTrack;

		// Must be empty
		TEST_ASSERT(track->getTitle() == NULL);
		TEST_ASSERT(track->stealTitle() == NULL);

		switch (i) {
		case 0:
			{
				// (A) Give track, copy memory, make owner of that copy
				bool const COPY = true;
				track->giveTitle(text, COPY);
			}
			break;

		case 1:
			{
				// (A) Give track, assign pointer, make track the owner
				bool const DONT_COPY = false;
				track->giveTitle(Toolbox::newAndCopy(text), DONT_COPY);
			}
			break;

		case 2:
		default:
			// (B) Lend track, assign pointer, stay owner
			track->lendTitle(text);

		}

		// Data arrived?
		TEST_ASSERT(track->getTitle() != NULL);

		// Steal == get memory ownership and remove from track
		XML_Char * stolen = track->stealTitle();
		TEST_ASSERT(stolen != NULL);

		// Must be gone
		TEST_ASSERT(track->getTitle() == NULL);
		TEST_ASSERT(track->stealTitle() == NULL);

		delete track;
		delete [] stolen;
	}
	TEST_ASSERT(i == 3);
}
