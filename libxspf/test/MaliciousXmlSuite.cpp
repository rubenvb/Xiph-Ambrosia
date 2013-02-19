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

#include "MaliciousXmlSuite.h"
#include <xspf/XspfReader.h>
#include <cstring>
using namespace Xspf;


MaliciousXmlSuite::MaliciousXmlSuite() {
	TEST_ADD(MaliciousXmlSuite::testDisabled)
	TEST_ADD(MaliciousXmlSuite::testLengthPerEntityValue)
	TEST_ADD(MaliciousXmlSuite::testLookupSumPerEntityValue)
	TEST_ADD(MaliciousXmlSuite::testLookupDepthPerEntityValue)
	TEST_ADD(MaliciousXmlSuite::testBillionLaughs1)
	TEST_ADD(MaliciousXmlSuite::testBillionLaughs2)
}


void
MaliciousXmlSuite::testDisabled() {
	char const * const document =
	"<!DOCTYPE d [\n"
	"\t<!ENTITY ld0 \"foo\">\n"
	"\t<!ENTITY ld1 \"&ld0;\">\n"
	"\t<!ENTITY ld2 \"&ld1;\">\n"
	"\t<!ENTITY ld3 \"&ld2;\">\n"
	"\t<!ENTITY ld4 \"&ld3;\">\n"
	"\t<!ENTITY ld5 \"&ld4;\">\n"
	"\t<!ENTITY ld6 \"&ld5;\">\n"
	"]>\n"
	"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n"
	"\t<title>&ld6;</title>\n"
	"\t<trackList />\n"
	"</playlist>\n"
	;

	XspfReader reader;
	int res; // no init needed

	// Disabled by default
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_SUCCESS);

	// Enabled manually
	reader.limitLookupDepthPerEntityValue(true);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_ERROR_MALICIOUS_LOOKUP_DEPTH);

	// Disabled manually
	reader.limitLookupDepthPerEntityValue(false);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_SUCCESS);
}


void
MaliciousXmlSuite::testLengthPerEntityValue() {
	char const * const document =
	"<!DOCTYPE d [\n"
	"\t<!ENTITY b10 \"xxxxxxxxxx\">\n"
	"\t<!ENTITY b20 \"&b10;&b10;\">\n"
	"]>\n"
	"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n"
	"\t<title>&b20;</title>\n"
	"\t<trackList />\n"
	"</playlist>\n"
	;

	XspfReader reader;
	reader.limitLengthPerEntityValue(true);
	int res; // no init needed

	// Limit too small
	reader.setMaxLengthPerEntityValue(19);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
			NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_ERROR_MALICIOUS_SPACE);

	// Limit at minimum
	reader.setMaxLengthPerEntityValue(20);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
			NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_SUCCESS);
}


void
MaliciousXmlSuite::testLookupSumPerEntityValue() {
	char const * const document =
	"<!DOCTYPE d [\n"
	"\t<!ENTITY ls0 \"foo\">\n"
	"\t<!ENTITY ls4 \"&ls0;&ls0;&ls0;&ls0;\">\n"
	"\t<!ENTITY ls10 \"&ls4;&ls4;\">\n"
	"]>\n"
	"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n"
	"\t<title>&ls10;</title>\n"
	"\t<trackList />\n"
	"</playlist>\n"
	;

	XspfReader reader;
	reader.limitLookupSumPerEntityValue(true);
	int res; // no init needed

	// Limit too small
	reader.setMaxLookupSumPerEntityValue(9);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_ERROR_MALICIOUS_LOOKUP_SUM);

	// Limit at minimum
	reader.setMaxLookupSumPerEntityValue(10);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_SUCCESS);
}


void
MaliciousXmlSuite::testLookupDepthPerEntityValue() {
	char const * const document =
	"<!DOCTYPE d [\n"
	"\t<!ENTITY ld0 \"foo\">\n"
	"\t<!ENTITY ld1 \"&ld0;\">\n"
	"\t<!ENTITY ld2 \"&ld1;\">\n"
	"\t<!ENTITY ld3 \"&ld2;\">\n"
	"]>\n"
	"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n"
	"\t<title>&ld3;</title>\n"
	"\t<trackList />\n"
	"</playlist>\n"
	;

	XspfReader reader;
	reader.limitLookupDepthPerEntityValue(true);
	int res; // no init needed

	// Limit too small
	reader.setMaxLookupDepthPerEntityValue(2);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_ERROR_MALICIOUS_LOOKUP_DEPTH);

	// Limit at minimum
	reader.setMaxLookupDepthPerEntityValue(3);
	res = reader.parseMemory(document, static_cast<int>(::strlen(document)),
		NULL, _PT("http://example.org/"));
	TEST_ASSERT(res == XSPF_READER_SUCCESS);
}


void
MaliciousXmlSuite::runMaliciousXml(char const * document) {
	XspfReader reader;
	for (int i = 1; i <= 3; i++) {
		int expectedRes; // no init needed
		switch (i) {
		case 1:
			reader.limitLengthPerEntityValue(true);
			reader.limitLookupSumPerEntityValue(false);
			reader.limitLookupDepthPerEntityValue(false);
			expectedRes = XSPF_READER_ERROR_MALICIOUS_SPACE;
			break;

		case 2:
			reader.limitLengthPerEntityValue(false);
			reader.limitLookupSumPerEntityValue(true);
			reader.limitLookupDepthPerEntityValue(false);
			expectedRes = XSPF_READER_ERROR_MALICIOUS_LOOKUP_SUM;
			break;

		case 3:
			reader.limitLengthPerEntityValue(false);
			reader.limitLookupSumPerEntityValue(false);
			reader.limitLookupDepthPerEntityValue(true);
			expectedRes = XSPF_READER_ERROR_MALICIOUS_LOOKUP_DEPTH;
			break;

		default:
			TEST_ASSERT(false);
		}

		int const res = reader.parseMemory(document,
				static_cast<int>(::strlen(document)),
				NULL, _PT("http://example.org/"));
		TEST_ASSERT(res == expectedRes);
	}
}


void
MaliciousXmlSuite::testBillionLaughs1() {
	// From http://www.cogsci.ed.ac.uk/~richard/billion-laughs.xml
	char const * const document =
	"<?xml version=\"1.0\"?>\n"
	"<!DOCTYPE billion [\n"
	"<!ELEMENT billion (#PCDATA)>\n"
	"<!ENTITY laugh0 \"ha\">\n"
	"<!ENTITY laugh1 \"&laugh0;&laugh0;\">\n"
	"<!ENTITY laugh2 \"&laugh1;&laugh1;\">\n"
	"<!ENTITY laugh3 \"&laugh2;&laugh2;\">\n"
	"<!ENTITY laugh4 \"&laugh3;&laugh3;\">\n"
	"<!ENTITY laugh5 \"&laugh4;&laugh4;\">\n"
	"<!ENTITY laugh6 \"&laugh5;&laugh5;\">\n"
	"<!ENTITY laugh7 \"&laugh6;&laugh6;\">\n"
	"<!ENTITY laugh8 \"&laugh7;&laugh7;\">\n"
	"<!ENTITY laugh9 \"&laugh8;&laugh8;\">\n"
	"<!ENTITY laugh10 \"&laugh9;&laugh9;\">\n"
	"<!ENTITY laugh11 \"&laugh10;&laugh10;\">\n"
	"<!ENTITY laugh12 \"&laugh11;&laugh11;\">\n"
	"<!ENTITY laugh13 \"&laugh12;&laugh12;\">\n"
	"<!ENTITY laugh14 \"&laugh13;&laugh13;\">\n"
	"<!ENTITY laugh15 \"&laugh14;&laugh14;\">\n"
	"<!ENTITY laugh16 \"&laugh15;&laugh15;\">\n"
	"<!ENTITY laugh17 \"&laugh16;&laugh16;\">\n"
	"<!ENTITY laugh18 \"&laugh17;&laugh17;\">\n"
	"<!ENTITY laugh19 \"&laugh18;&laugh18;\">\n"
	"<!ENTITY laugh20 \"&laugh19;&laugh19;\">\n"
	"<!ENTITY laugh21 \"&laugh20;&laugh20;\">\n"
	"<!ENTITY laugh22 \"&laugh21;&laugh21;\">\n"
	"<!ENTITY laugh23 \"&laugh22;&laugh22;\">\n"
	"<!ENTITY laugh24 \"&laugh23;&laugh23;\">\n"
	"<!ENTITY laugh25 \"&laugh24;&laugh24;\">\n"
	"<!ENTITY laugh26 \"&laugh25;&laugh25;\">\n"
	"<!ENTITY laugh27 \"&laugh26;&laugh26;\">\n"
	"<!ENTITY laugh28 \"&laugh27;&laugh27;\">\n"
	"<!ENTITY laugh29 \"&laugh28;&laugh28;\">\n"
	"<!ENTITY laugh30 \"&laugh29;&laugh29;\">\n"
	"]>\n"
	"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n"
	"\t<title>&laugh30;</title>\n"
	"\t<trackList />\n"
	"</playlist>\n"
	;

	runMaliciousXml(document);
}


void
MaliciousXmlSuite::testBillionLaughs2() {
	// From http://www.ruby-lang.org/en/news/2008/08/23/dos-vulnerability-in-rexml/
	char const * const document =
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	"<!DOCTYPE member [\n"
	"  <!ENTITY g \"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\">\n"
	"  <!ENTITY f \"&g;&g;&g;&g;&g;&g;&g;&g;&g;&g;\">\n"
	"  <!ENTITY e \"&f;&f;&f;&f;&f;&f;&f;&f;&f;&f;\">\n"
	"  <!ENTITY d \"&e;&e;&e;&e;&e;&e;&e;&e;&e;&e;\">\n"
	"  <!ENTITY c \"&d;&d;&d;&d;&d;&d;&d;&d;&d;&d;\">\n"
	"  <!ENTITY b \"&c;&c;&c;&c;&c;&c;&c;&c;&c;&c;\">\n"
	"  <!ENTITY a \"&b;&b;&b;&b;&b;&b;&b;&b;&b;&b;\">\n"
	"]>\n"
	"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">\n"
	"\t<title>&a;</title>\n"
	"\t<trackList />\n"
	"</playlist>\n"
	;

	runMaliciousXml(document);
}
