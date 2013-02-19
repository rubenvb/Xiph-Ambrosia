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
#include <cassert>
using namespace Xspf;


#if defined(__WIN32__) || defined(WIN32)
# if defined(UNICODE)
#  define PORT_COUT std::wcout
# else
#  define PORT_COUT std::cout
# endif
#else
# define PORT_COUT std::cout
#endif


class Validator : public XspfReaderCallback {

private:
	int version;
	bool valid;
	bool fatal;
	bool loose;

public:
	Validator(bool loose)
			: version(-1), valid(true), fatal(false), loose(loose) {

	}

	bool isValid() {
		return loose ? !fatal : valid;
	}

private:
	void setProps(XspfProps * props) {
		this->version = props->getVersion();
		delete props;
	}

	void handle(int line, int column, int code,
			XML_Char const * description, bool isError) {
		assert(description != NULL);
		PORT_COUT << (isError ? "Error" : "Warning")
				<< " (line " << line
				<< ", col " << column
				<< "): \"" << std::basic_string<XML_Char>(description) << "\""
				<< std::endl << std::flush;
	}

	void notifyFatalError(int line, int column, int errorCode,
			XML_Char const * description) {
		valid = false;
		fatal = true;
		handle(line, column, errorCode, description, true);
	}

	bool handleError(int line, int column, int errorCode,
			XML_Char const * description) {
		valid = false;
		handle(line, column, errorCode, description, !loose);
		return true; // Continue parsing
	}

	bool handleWarning(int line, int column, int warningCode,
			XML_Char const * description) {
		handle(line, column, warningCode, description, false);
		return true; // Continue parsing
	}

	void notifySuccess() {
		if (valid) {
			std::cout << "Valid XSPF-" << this->version << "."
					<< std::endl << std::flush;
		} else if (loose && !fatal) {
			std::cout << "Not valid XSPF, still readable "
					<< "by libxspf " << XSPF_VER_MAJOR << "."
					<< XSPF_VER_MINOR << "." << XSPF_VER_RELEASE
					<< XSPF_VER_SUFFIX_ASCII << "."
					<< std::endl << std::flush;
		}
	}

};


int
printUsage() {
	std::cout << "USAGE: xspf_check ([--loose] -|--version)" << std::endl << std::flush;
	return 1;
}


int
printVersion() {
	std::cout << "xspf_check "
			<< XSPF_VER_MAJOR << "."
			<< XSPF_VER_MINOR << "."
			<< XSPF_VER_RELEASE
			<< XSPF_VER_SUFFIX_ASCII
			<< std::endl << std::flush;
	return 0;
}


int
checkStdin(bool loose) {
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
	char const * memory = input.c_str();
	int const numBytes = static_cast<int>(strlen(memory));

	// Valid XSPF?
	XspfReader reader;
	Validator validator(loose);
	int const res = reader.parseMemory(memory, numBytes, &validator,
			_PT("http://www.example.org/"));
	return validator.isValid() ? 0 : 1;
}


int
main(int argc, char ** argv) {
	bool loose = false;
	bool usage = false;
	bool error = false;
	bool fromStdin = false;
	bool version = false;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			error = true;
			break;
		}

		if (argv[i][1] == '\0') {
			fromStdin = true;
		} else if (!strcmp(argv[i] + 1, "-version")) {
			version = true;
		} else if (!strcmp(argv[i] + 1, "-loose")) {
			loose = true;
		} else {
			error = true;
		}
	}

	if (!usage && !version && !fromStdin) {
		usage = true;
		error = true;
	}

	if (error) {
		printUsage();
		return 1;
	}

	if (usage) {
		printUsage();
		return 0;
	}

	if (version) {
		printVersion();
		return 0;
	}

	return checkStdin(loose);
}
