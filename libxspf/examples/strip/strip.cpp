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

#include <xspf/Xspf.h>
#include <iostream>
#include <list>
#include <cassert>
using namespace Xspf;


class Collector : public XspfReaderCallback {

private:
	std::list<XspfTrack *> * tracks;
	XspfProps * props;

public:
	Collector() : tracks(new std::list<XspfTrack *>()), props(NULL) {

	}

	std::list<XspfTrack *> * stealTracks() {
		std::list<XspfTrack *> * backup = this->tracks;
		this->tracks = NULL;
		return backup;
	}

	XspfProps * stealProps() {
		XspfProps * backup = this->props;
		this->props = NULL;
		return backup;
	}

	~Collector() {
		if (this->tracks != NULL) {
			std::list<XspfTrack *>::iterator iter = this->tracks->begin();
			while (iter != this->tracks->end()) {
				XspfTrack * const track = *iter;
				delete track;
				iter++;
			}
			delete this->tracks;
		}
		if (this->props != NULL) {
			delete this->props;
		}
	}

private:
	void addTrack(XspfTrack * track) {
		this->tracks->push_back(track);
	}

	void setProps(XspfProps * props) {
		this->props = props;
	}

};


int printUsage() {
	std::cout << "USAGE: xspf_strip (-|--version)" << std::endl << std::flush;
	return 1;
}


int printVersion() {
	std::cout << "xspf_strip "
			<< XSPF_VER_MAJOR << "."
			<< XSPF_VER_MINOR << "."
			<< XSPF_VER_RELEASE
			<< XSPF_VER_SUFFIX
			<< std::endl << std::flush;
	return 0;
}


int filterStdinStdout() {
	// Read until EOF
	std::stringbuf buffer;
	for (;;) {
		char const c = std::cin.get();
		if (c == -1) {
			break;
		}
		buffer.sputc(c);
	}

	// Convert to byte array
	const std::string input = buffer.str();
	char const * inputMemory = input.c_str();
	int const inputNumBytes = static_cast<int>(strlen(inputMemory));

	// Parse and collect
	XspfReader reader;
	Collector collector;
	// XML_Char const * const stdinBaseUri = _PT("http://purl.org/posix/stdin");
	// XML_Char const * const stdinBaseUri = _PT("std:in");
	// XML_Char const * const stdinBaseUri = _PT("file:stdin");
	XML_Char const * const stdinBaseUri = _PT("file:///dev/stdin");
	int const res = reader.parseMemory(inputMemory, inputNumBytes,
			&collector, stdinBaseUri);
	if (res != XSPF_READER_SUCCESS) {
		// Error
		return 1;
	}

	// Steal collected information
	std::list<XspfTrack *> * const tracks = collector.stealTracks();
	XspfProps * const props = collector.stealProps();

	// Version 0, well-indented XML
	XspfIndentFormatter formatter;
	XspfWriter * const writer = XspfWriter::makeWriter(
			formatter, stdinBaseUri);
	assert(writer != NULL);
	props->setVersion(0);
	writer->setProps(props);
	delete props;

	// Write all tracks
	std::list<XspfTrack *>::iterator iter = tracks->begin();
	while (iter != tracks->end()) {
		XspfTrack * const track = *iter;
		writer->addTrack(track);
		delete track;
		iter++;
	}

	// Write to memory block
	char * outputMemory;
	int outputNumBytes;
	bool success = (XSPF_WRITER_SUCCESS == writer->writeMemory(
			outputMemory, outputNumBytes));
	delete writer;
	if (!success) {
		return 1;
	}

	std::cout.write(outputMemory, outputNumBytes);
	delete [] outputMemory;

	return 0;
}


int main(int argc, char ** argv) {
	switch (argc) {
	case 2:
		if (argv[1][0] != '-') {
			// Invalid parameter
			return printUsage();
		}

		if (argv[1][1] == '\0') {
			return filterStdinStdout();
		} else if (!strcmp(argv[1] + 1, "-version")) {
			return printVersion();
		}
		return printUsage();

	case 1: // No params
	default:
		return printUsage();

	}
}
