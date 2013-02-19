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

#include "ChunkCallbackSuite.h"
#include <xspf/XspfReader.h>
#include <cstring>
using namespace Xspf;


ChunkCallbackSuite::ChunkCallbackSuite() {
	TEST_ADD(ChunkCallbackSuite::validOneGo)
	TEST_ADD(ChunkCallbackSuite::valid)
	TEST_ADD(ChunkCallbackSuite::invalid)
	TEST_ADD(ChunkCallbackSuite::validGrowSize)
}


void ChunkCallbackSuite::reset(XML_Char const ** lines,
		int numLines, int expextedRes, int errorLine) {
	this->lines = lines;
	this->numLines = numLines;
	this->expextedRes = expextedRes;
	this->errorLine = errorLine;
	this->curLine = 0;
	this->stopCalled = false;
}


void ChunkCallbackSuite::run() {
	XspfReader reader;
	int const res = reader.parseChunks(this, NULL, _PT("http://www.example.org/"));
	TEST_ASSERT(res == this->expextedRes);
	if (this->expextedRes == XSPF_READER_SUCCESS) {
		TEST_ASSERT(this->curLine == this->numLines);
	} else {
		TEST_ASSERT((this->curLine - 1) == this->errorLine);
	}
	TEST_ASSERT(this->stopCalled);
}


void ChunkCallbackSuite::validOneGo() {
	XML_Char const ** const validLines = new const XML_Char *[1];
#ifdef UNICODE
	validLines[0] = _PT("<?xml version=\"1.0\" encoding=\"UTF-16\"?>\n")
#else
	validLines[0] = _PT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
#endif
			_PT("<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n")
			_PT("\t<trackList />\n")
			_PT("</playlist>\n");
	reset(validLines, 1, XSPF_READER_SUCCESS);
	run();
	delete [] validLines;
}


void ChunkCallbackSuite::valid() {
	XML_Char const ** const validLines = new const XML_Char *[4];
#ifdef UNICODE
	validLines[0] = _PT("<?xml version=\"1.0\" encoding=\"UTF-16\"?>\n");
#else
	validLines[0] = _PT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
#endif
	validLines[1] = _PT("<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n");
	validLines[2] = _PT("\t<trackList />\n");
	validLines[3] = _PT("</playlist>\n");
	reset(validLines, 4, XSPF_READER_SUCCESS);
	run();
	delete [] validLines;
}


void ChunkCallbackSuite::invalid() {
	XML_Char const ** const invalidLines = new const XML_Char *[4];
#ifdef UNICODE
	invalidLines[0] = _PT("<?xml version=\"1.0\" encoding=\"UTF-16\"?>\n");
#else
	invalidLines[0] = _PT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
#endif
	invalidLines[1] = _PT("<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n");
	invalidLines[2] = _PT("\t<FORBIDDEN />\n");
	invalidLines[3] = _PT("</playlist>\n");
	reset(invalidLines, 4, XSPF_READER_ERROR_ELEMENT_FORBIDDEN, 2);
	run();
	delete [] invalidLines;
}


void ChunkCallbackSuite::validGrowSize() {
	XML_Char const ** const validLines = new const XML_Char *[15];
	validLines[ 0] = _PT("<");
	validLines[ 1] = _PT("?x");
	validLines[ 2] = _PT("ml ");
	validLines[ 3] = _PT("vers");
	validLines[ 4] = _PT("ion=\"");
	validLines[ 5] = _PT("1.0\" e");
	validLines[ 6] = _PT("ncoding");
#ifdef UNICODE
	validLines[ 7] = _PT("=\"UTF-16\"");
#else
	validLines[ 7] = _PT("=\"UTF-8\"");
#endif
	validLines[ 8] = _PT("?>\n<playl");
	validLines[ 9] = _PT("ist versio");
	validLines[10] = _PT("n=\"1\" xmlns");
	validLines[11] = _PT("=\"http://xsp");
	validLines[12] = _PT("f.org/ns/0/\">");
	validLines[13] = _PT("\n\t<trackList />");
	validLines[14] = _PT("\n</playlist>\n");
	reset(validLines, 15, XSPF_READER_SUCCESS);
	run();
	delete [] validLines;
}


int ChunkCallbackSuite::getMinimumBufferByteSize() {
	if (this->curLine < numLines) {
		return sizeof(XML_Char) * static_cast<int>(PORT_STRLEN(
				this->lines[this->curLine]));
	} else {
		return 0;
	}
}


int ChunkCallbackSuite::fillBuffer(void * buffer) {
	if (this->curLine < numLines) {
		int const byteLen = static_cast<int>(PORT_STRLEN(this->lines[this->curLine]))
				* sizeof(XML_Char);
		memcpy(buffer, this->lines[this->curLine], byteLen);
		this->curLine++;
		return byteLen;
	} else {
		return 0;
	}
}


void ChunkCallbackSuite::notifyStop() {
	this->stopCalled = true;
}
