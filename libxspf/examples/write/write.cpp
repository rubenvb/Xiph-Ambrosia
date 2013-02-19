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
#include <xspf/ProjectOpus/ProjectOpusPlaylistExtension.h>
#include <cstdio>
#include <cassert>
using namespace Xspf;
using namespace Xspf::Toolbox;
using namespace Xspf::ProjectOpus;


void
fillProps(XspfProps & props) {
	// NOTE: When writing please make URIs relative where it makes sense.
	// Most importantly this applies to track locations, so the playlist
	// files can be moved along with the files.
	// XspfToolbox::makeRelativeUri() can do that job for you.
	// An example usage is shown below.
	props.giveTitle(_PT("Now playing"), XspfData::COPY);
	props.giveAnnotation(_PT("Well, ..."), XspfData::COPY);
	props.giveCreator(_PT("libxspf XSPF library"), XspfData::COPY);
	XspfDateTime dateTime(2006, 8, 28, 11, 30, 11, 1, 0);
	props.giveDate(&dateTime, XspfData::COPY);
	props.giveIdentifier(_PT("xspf:libxspf:testId"), XspfData::COPY);
	props.giveImage(_PT("some/image.png"), XspfData::COPY);
	props.giveInfo(_PT("http://info/info"), XspfData::COPY);
	props.giveLicense(_PT("http://license/free/"), XspfData::COPY);
	props.giveLocation(_PT("http://playlist/home.xspf"), XspfData::COPY);
	props.setVersion(0);
	props.giveAppendAttributionIdentifier(_PT("some:any/many"), XspfData::COPY);
	props.giveAppendAttributionLocation(_PT("test:pest/west"), XspfData::COPY);
	props.giveAppendLink(_PT("store:url"), XspfData::COPY,
			_PT("http://expensive/dot/com"), XspfData::COPY);
	props.giveAppendMeta(_PT("tag:meta:year"), XspfData::COPY, _PT("2006"), XspfData::COPY);

	// Add a playlist extension
	ProjectOpusPlaylistExtension playlistExtension;
	playlistExtension.setNodeId(123);
	playlistExtension.setType(TYPE_ALBUM);
	props.giveAppendExtension(&playlistExtension, XspfData::COPY);
}


void
fillTrack(XspfTrack & track) {
	// NOTE: When writing please make URIs relative where it makes sense.
	// Most importantly this applies to track locations, so the playlist
	// files can be moved along with the files.
	// XspfToolbox::makeRelativeUri() can do that job for you.
	// An example usage is shown below.
	track.giveAlbum(_PT("Phobia"), XspfData::COPY);
	track.giveCreator(_PT("Breaking Benjamin"), XspfData::COPY);
	track.giveTitle(_PT("Unknown Soldier"), XspfData::COPY);
	track.setTrackNum(10);
	track.giveAppendIdentifier(_PT("id:bb:unknownSoldier"), XspfData::COPY);
	track.giveAppendLink(_PT("http://meta/key/uri/here"), XspfData::COPY,
			_PT("http://website"), XspfData::COPY);
	track.giveAppendLocation(
			_PT("http://example.org/10_unknown_soldier.ogg"), XspfData::COPY);
	track.giveAppendMeta(_PT("tag:meta:year"), XspfData::COPY, _PT("2006"), XspfData::COPY);
	track.giveAnnotation(_PT("Great song"), XspfData::COPY);
	track.setDuration(123000);
	track.giveImage(
			_PT("http://example.org/some/image.png"), XspfData::COPY);
	track.giveInfo(_PT("http://info/info"), XspfData::COPY);
}


int
PORT_MAIN() {
	XML_Char const * const baseUri = _PT("http://example.org/");
	XML_Char const * const relativeFilename = _PT("TEST.xspf");

	// Set up playlist props
	XspfProps props;
	fillProps(props);

	// Version 1, well-indented XML
	XspfIndentFormatter formatter;
	XspfWriter * const writer = XspfWriter::makeWriter(
			formatter, baseUri, XspfWriter::EMBED_AS_XML_BASE);
	assert(writer != NULL);

	// Pre-register extension namespace so
	// it can appear in <playlist> already
	writer->registerNamespace(ProjectOpusPlaylistExtension
			::namespaceKey, _PT("po"));

	// Set up track
	XspfTrack track;
	fillTrack(track);

	// Add track two times
	writer->addTrack(track);
	writer->addTrack(track);

	// Finish and write to file
	int const res = writer->writeFile(relativeFilename);
	delete writer;
	if (res != XSPF_WRITER_SUCCESS) {
		PORT_PRINTF(_PT("Could not write to file.\n"));
		return 1;
	} else {
		PORT_PRINTF(_PT("Everything fine.\n"));
		return 0;
	}
}
