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

#ifndef XSPF_TEST_CHUNK_CALLBACK_SUITE_H
#define XSPF_TEST_CHUNK_CALLBACK_SUITE_H 1


#include <cpptest.h>
#include <xspf/XspfChunkCallback.h>
#include <xspf/XspfDefines.h>


class ChunkCallbackSuite : public Test::Suite,
		public Xspf::XspfChunkCallback {

private:
	XML_Char const ** lines;
	int numLines;
	int expextedRes;
	int errorLine;
	int curLine;
	bool stopCalled;

public:
	ChunkCallbackSuite();

private:
	void reset(XML_Char const ** lines, int numLines,
			int expextedRes, int errorLine = -1);
	void run();

	// Tests
	void validOneGo();
	void valid();
	void invalid();
	void validGrowSize();

	int getMinimumBufferByteSize();
	int fillBuffer(void * buffer);
	void notifyStop();

};


#endif // XSPF_TEST_CHUNK_CALLBACK_SUITE_H
