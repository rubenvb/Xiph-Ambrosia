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

#include "ReadWriteSuite.h"
#include <xspf/XspfProps.h>
#include <xspf/XspfIndentFormatter.h>
#include <xspf/XspfReader.h>
#include <xspf/XspfReaderCallback.h>
#include <xspf/XspfTrack.h>
#include <xspf/XspfWriter.h>
#include <cstring>
using namespace Xspf;


ReadWriteSuite::ReadWriteSuite() {
	TEST_ADD(ReadWriteSuite::testRelativeUris);
	TEST_ADD(ReadWriteSuite::testXmlBaseStack);
}


class PropsGrabberCallback : public XspfReaderCallback {

private:
	XspfProps * m_props;
	XspfTrack * m_track;

	void setProps(XspfProps * props) {
		delete m_props;
		m_props = props;
	}

	void addTrack(XspfTrack * track) {
		delete m_track;
		m_track = track;
	}

public:
	PropsGrabberCallback() : m_props(NULL), m_track(NULL) { }

	~PropsGrabberCallback() {
		delete m_props;
		m_props = NULL;
		delete m_track;
		m_track = NULL;
	}

	XspfProps * getProps() const { return m_props; }
	XspfTrack * getTrack() const { return m_track; }
};


void ReadWriteSuite::testRelativeUris() {
	XspfProps props;
	XspfTrack track;

	for (int i = 0; i < 3; i++) {
		// Write to memory
///////////////////////////////////////////////////////////////////////////////
		XML_Char const * const baseUriOne = _PT("http://example.org/one/");
		XML_Char const * const baseUriTwo = _PT("http://example.org/two/");
			
		XML_Char const * const imageUriOne = _PT("http://example.org/one/image.png");
		XML_Char const * const imageUriTwo = _PT("http://example.org/two/image.png");

		props.lendImage(imageUriOne);
		track.lendImage(imageUriOne);
///////////////////////////////////////////////////////////////////////////////

		XspfIndentFormatter layout;
		XspfWriter * writer;
		int errorCode;
		switch (i) {
		case 0: // With base URI, embedded
			writer = XspfWriter::makeWriter(
					layout, baseUriOne,
					XspfWriter::EMBED_AS_XML_BASE, &errorCode);
			break;
		case 1: // With base URI, _not_ embedded
			writer = XspfWriter::makeWriter(
					layout,  baseUriOne,
					XspfWriter::NO_XML_BASE, &errorCode);
			break;
		case 2: // No base URI, all URIs absolute
			writer = XspfWriter::makeWriter(
					layout, NULL, true, &errorCode);
			break;
		default:
			TEST_ASSERT(false);
		}
		TEST_ASSERT(writer != NULL);
		TEST_ASSERT(errorCode == XSPF_WRITER_SUCCESS);
		writer->setProps(props);
		writer->addTrack(track);
		char * output = new char[5000];
		int numBytes = 5000;
		int const writeRes = writer->writeMemory(output, numBytes);
		TEST_ASSERT(writeRes == 0);
		TEST_ASSERT(numBytes > 0);
		TEST_ASSERT(output[0] != '\0');

		// Read back from memory
		XspfReader reader;
		PropsGrabberCallback propsGrabber;
		int const readRes = reader.parseMemory(output, numBytes,
				&propsGrabber, baseUriTwo);
		TEST_ASSERT(readRes == XSPF_READER_SUCCESS);

		// Compare
		XspfProps * const afterProps = propsGrabber.getProps();
		TEST_ASSERT(afterProps != NULL);
		XspfTrack * const afterTrack = propsGrabber.getTrack();
		TEST_ASSERT(afterTrack != NULL);
///////////////////////////////////////////////////////////////////////////////
		XML_Char const * const givenPropsImage = afterProps->getImage();
		XML_Char const * expectedImage = NULL;
		switch (i) {
		case 0: // With base URI, embedded
			expectedImage = imageUriOne;
			break;
		case 1: // With base URI, _not_ embedded
			expectedImage = imageUriTwo;
			break;
		case 2: // No base URI, all URIs absolute
			expectedImage = imageUriOne;
			break;
		default:
			TEST_ASSERT(false);
		}
		TEST_ASSERT(!::PORT_STRCMP(givenPropsImage, expectedImage));

		XML_Char const * const givenTrackImage = afterTrack->getImage();
		XML_Char const * const expectedTrackImage = imageUriTwo;
		TEST_ASSERT(!::PORT_STRCMP(givenTrackImage, expectedImage));
///////////////////////////////////////////////////////////////////////////////

		delete [] output;
		delete writer;
	}
}


class XmlBaseComparatorCallback : public XspfReaderCallback {

private:
	int i;

public:
	bool success;

private:
	void addTrack(XspfTrack * track) {
		if (!success) {
			return;
		}

		XML_Char const * given = track->getLocation(0);
		XML_Char const * expected = NULL;
		switch (i) {
		case 0:
			expected = _PT("http://example.org/a/b/c/d/0");
			break;
		case 1:
			expected = _PT("http://example.org/a/b/e/1");
			break;
		case 2:
			expected = _PT("http://example.org/a/b/f/2");
			break;
		case 3:
			expected = _PT("http://example.org/a/b/3");
			break;
		case 4:
			expected = _PT("http://example.org/g/4");
			break;
		case 5:
			expected = _PT("http://example.org/h/i/5");
			break;
		default:
			success = false;
			delete track;
			return;
		}
		i++;

		success = !::PORT_STRCMP(given, expected);
		delete track;
	}

public:
	XmlBaseComparatorCallback() : i(0), success(true) { }
};


void ReadWriteSuite::testXmlBaseStack() {
	char const * const content =
"<?xml version=\"1.0\"?>\n"
"<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\" xml:base=\"a/\">\n"
"  <trackList xml:base=\"b/\">\n"
"    <track xml:base=\"c/\">\n"
"      <location xml:base=\"d/\">0</location>\n"
"    </track>\n"
"    <track xml:base=\"e/\">\n"
"      <location>1</location>\n"
"    </track>\n"
"    <track>\n"
"      <location xml:base=\"f/\">2</location>\n"
"    </track>\n"
"    <track>\n"
"      <location>3</location>\n"
"    </track>\n"
"    <track xml:base=\"http://example.org/g/\">\n"
"      <location>4</location>\n"
"    </track>\n"
"    <track xml:base=\"http://example.org/h/\">\n"
"      <location xml:base=\"i/\">5</location>\n"
"    </track>\n"
"  </trackList>\n"
"</playlist>\n"
	;

	XmlBaseComparatorCallback callback;
	XspfReader reader;
	XML_Char const * const baseUri = _PT("http://example.org/");
	int const res = reader.parseMemory(content,
			static_cast<int>(::strlen(content)), &callback, baseUri);
	TEST_ASSERT(res == XSPF_READER_SUCCESS);
	TEST_ASSERT(callback.success);
}
