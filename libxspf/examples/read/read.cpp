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
#include <uriparser/Uri.h>
#include <cstdio>
#include <cstdlib> // MAX_PATH
#include <climits> // PATH_MAX


#if defined(__WIN32__) || defined(WIN32)
# define DIR_SEPERATOR '\\'
# define PORT_PATH_MAX MAX_PATH
# if defined(UNICODE)
#  define uriFilenameToUriString uriWindowsFilenameToUriStringW
# define PORT_GETCWD _wgetcwd
# else
#  define uriFilenameToUriString uriWindowsFilenameToUriStringA
#  define PORT_GETCWD _getcwd
# endif
#else
# define PORT_PATH_MAX PATH_MAX
# define DIR_SEPERATOR '/'
# define uriFilenameToUriString uriUnixFilenameToUriStringA
# define PORT_GETCWD getcwd
#endif


using namespace Xspf;


class DemoReaderCallback : public XspfReaderCallback {

	bool valid;

public:
	DemoReaderCallback() : valid(true) {

	}

private:
	void addTrack(XspfTrack * track) {
		open(_PT("Track"));
			printKeyValue(_PT("Album"), track->getAlbum());
			printKeyValue(_PT("Annotation"), track->getAnnotation());
			printKeyValue(_PT("Creator"), track->getCreator());
			printKeyValue(_PT("Duration"), track->getDuration());
			printIdentifierSummary(track);
			printKeyValue(_PT("Image"), track->getImage());
			printKeyValue(_PT("Info"), track->getInfo());
			printLinkSummay<XspfTrack>(track);
			printLocationSummary(track);
			printMetaSummary<XspfTrack>(track);
			printKeyValue(_PT("Title"), track->getTitle());
			printKeyValue(_PT("TrackNum"), track->getTrackNum());
		close();
		delete track;
	}

	void setProps(XspfProps * props) {
		open(_PT("Props"));
			printKeyValue(_PT("Annotation"), props->getAnnotation());
			printAttributionSummary(props);
			printKeyValue(_PT("Creator"), props->getCreator());
			printKeyValue(_PT("Date"), props->getDate());

			printKeyValue(_PT("Identifier"), props->getIdentifier());
			printKeyValue(_PT("Image"), props->getImage());
			printKeyValue(_PT("Info"), props->getInfo());
			printKeyValue(_PT("License"), props->getLicense());
			printLinkSummay<XspfProps>(props);
			printKeyValue(_PT("Location"), props->getLocation());
			printMetaSummary<XspfProps>(props);
			printKeyValue(_PT("Title"), props->getTitle());
			printKeyValue(_PT("Version"), props->getVersion());
		close();
		delete props;
	}

	bool handleError(int line, int column, int errorCode,
			XML_Char const * description) {
		PORT_PRINTF(_PT("Error %i at (line %i, column %i): '%s'\n"),
				errorCode, line, column, description);
		valid = false;
		return true; // Continue parsing
	}

	void notifySuccess() {
		if (valid) {
			PORT_PRINTF(_PT("Everything fine.\n"));
		}
	}

	static void open(XML_Char const * type) {
		PORT_PRINTF(_PT("%s\n"), type);
	}

	static void close() {
		PORT_PRINTF(_PT("\n"));
	}

	static void printKeyValue(XML_Char const * key, XML_Char const * value) {
		if (value == NULL) {
			PORT_PRINTF(_PT("\t%s: -\n"), key);
		} else {
			PORT_PRINTF(_PT("\t%s: '%s'\n"), key, value);
		}
	}

	static void printKeyValue(XML_Char const * key, int value) {
		if (value == -1) {
			PORT_PRINTF(_PT("\t%s: -\n"), key);
		} else {
			PORT_PRINTF(_PT("\t%s: '%i'\n"), key, value);
		}
	}

	static void printKeyValue(XML_Char const * key, XspfDateTime const * value) {
		if (value == NULL) {
			PORT_PRINTF(_PT("\t%s: -\n"), key);
		} else {
			PORT_PRINTF(_PT("\t%s: %04i-%02i-%02i %02i:%02i:%02i %s%02i:%02i\n"), key,
					value->getYear(), value->getMonth(), value->getDay(), value->getHour(), value->getMinutes(),
					value->getSeconds(), (value->getDistHours() < 0) ? _PT("-") : _PT("+"),
					std::abs(value->getDistHours()), std::abs(value->getDistMinutes()));
		}
	}

	static void printHelper(XML_Char const * key, int size) {
		PORT_PRINTF(_PT("\t%s: %i entr%s\n"), key, size, (size == 1) ? _PT("y") : _PT("ies"));
	}

	template <class T>
	static void printLinkSummay(T * data) {
		int const size = (static_cast<XspfData *>(data))->getLinkCount();
		printHelper(_PT("Links"), size);
	}

	template <class T>
	static void printMetaSummary(T * data) {
		int const size = (static_cast<XspfData *>(data))->getMetaCount();
		printHelper(_PT("Metas"), size);
	}

	static void printAttributionSummary(XspfProps * props) {
		int const size = props->getAttributionCount();
		printHelper(_PT("Attributions"), size);
	}

	static void printIdentifierSummary(XspfTrack * track) {
		int const size = track->getIdentifierCount();
		printHelper(_PT("Identifier"), size);
	}

	static void printLocationSummary(XspfTrack * track) {
		int const size = track->getLocationCount();
		printHelper(_PT("Locations"), size);
	}

};


/**
 * Creates a URI from an absolute filename for this host sytem.
 * 
 * @param fileName  Absolute filename
 * @return          New'ed Absolute URI or NULL on error
 */
XML_Char *
makeUriFromAbsoluteFilename(XML_Char const * fileName) {
	if (fileName == NULL) {
		return NULL;
	}

	size_t const len = ::PORT_STRLEN(fileName);
	size_t const charsNeeded = 8 + 3 * len + 1;
	XML_Char * const absUri = new XML_Char[charsNeeded];
	::uriFilenameToUriString(fileName, absUri);
	return absUri;
}


/**
 * Prepends the current working directory and a (back)slash
 * (depending on the host operating system) to the relative filename given.
 *
 * @param relativeFilename  Relative filename of host operating system
 * @return                  Absolute filename of host operating system
 */
XML_Char *
makeAbsoluteFilename(XML_Char const * relativeFilename) {
	if (relativeFilename == NULL) {
		return NULL;
	}
	size_t const relativeFilenameLen = ::PORT_STRLEN(relativeFilename);
	XML_Char * const absoluteFilename = new XML_Char[
			PORT_PATH_MAX + 1 + relativeFilenameLen + 1];
	XML_Char const * const res = ::PORT_GETCWD(absoluteFilename,
			PORT_PATH_MAX);
	if (res == NULL) {
		delete [] absoluteFilename;
		return NULL;
	}
	size_t const cwdLen = ::PORT_STRLEN(absoluteFilename);
	absoluteFilename[cwdLen] = _PT(DIR_SEPERATOR);
	::PORT_STRNCPY(absoluteFilename + cwdLen + 1, relativeFilename,
			relativeFilenameLen);
	absoluteFilename[cwdLen + 1 + relativeFilenameLen] = _PT('\0');
	return absoluteFilename;
}


int
PORT_MAIN() {
	XspfReader reader;
	XspfReaderCallback * callback = new DemoReaderCallback;

	// Make base URI
	XML_Char const * const relativeFilename = _PT("playlist.xspf");
	XML_Char * const absoluteFilename = makeAbsoluteFilename(relativeFilename);
	XML_Char * const baseUri = makeUriFromAbsoluteFilename(absoluteFilename);
	delete [] absoluteFilename;

	// Parse
	int const res = reader.parseFile(relativeFilename,
			callback, baseUri);
	delete [] baseUri;
	delete callback;

	return (res == XSPF_READER_SUCCESS) ? 0 : 1;
}
