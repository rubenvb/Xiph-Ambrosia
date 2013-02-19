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

#include "OfficialSuite.h"
#include <xspf/XspfReaderCallback.h>
using namespace Xspf;


#undef SEP
#if (defined(__WIN32__) || defined(WIN32))
# define SEP _PT("\\")
#else
# define SEP _PT("/")
#endif

#ifndef XSPF_SRCDIR
# define XSPF_SRCDIR "."
#endif

#define V0_FAIL_PATH     _PT(XSPF_SRCDIR) SEP _PT("test") SEP _PT("for_version_0") SEP _PT("fail") SEP
#define V0_PASS_PATH     _PT(XSPF_SRCDIR) SEP _PT("test") SEP _PT("for_version_0") SEP _PT("pass") SEP
#define V1_FAIL_PATH     _PT(XSPF_SRCDIR) SEP _PT("test") SEP _PT("for_version_1") SEP _PT("fail") SEP
#define V1_PASS_PATH     _PT(XSPF_SRCDIR) SEP _PT("test") SEP _PT("for_version_1") SEP _PT("pass") SEP


OfficialSuite::OfficialSuite() {
	// version 0 / fail
	TEST_ADD(OfficialSuite::playlist_extension_forbidden)
	TEST_ADD(OfficialSuite::track_extension_forbidden)
	TEST_ADD(OfficialSuite::tracklist_no_tracks)

	// version 0 / pass
	// none yet

	// version 1 / fail
	TEST_ADD(OfficialSuite::playlist_attribute_forbidden_annotation)
	TEST_ADD(OfficialSuite::playlist_attribute_forbidden_playlist)
	TEST_ADD(OfficialSuite::playlist_baddate)
	TEST_ADD(OfficialSuite::playlist_badversion)
	TEST_ADD(OfficialSuite::playlist_element_forbidden_attribution)
	TEST_ADD(OfficialSuite::playlist_extension_application_missing)
	TEST_ADD(OfficialSuite::playlist_link_rel_missing)
	TEST_ADD(OfficialSuite::playlist_markup_annotation)
	TEST_ADD(OfficialSuite::playlist_markup_creator)
	TEST_ADD(OfficialSuite::playlist_markup_meta)
	TEST_ADD(OfficialSuite::playlist_markup_title)
	TEST_ADD(OfficialSuite::playlist_meta_rel_missing)
	TEST_ADD(OfficialSuite::playlist_missingtracklist)
	TEST_ADD(OfficialSuite::playlist_missingversion)
	TEST_ADD(OfficialSuite::playlist_namespace_missing)
	TEST_ADD(OfficialSuite::playlist_namespace_nested_broken)
	TEST_ADD(OfficialSuite::playlist_namespace_wrong_string)
	TEST_ADD(OfficialSuite::playlist_nonleaf_content_attribution)
	TEST_ADD(OfficialSuite::playlist_nonleaf_content_playlist)
	TEST_ADD(OfficialSuite::playlist_nonleaf_content_trackList)
	TEST_ADD(OfficialSuite::playlist_noturi_attribution_identifier)
	TEST_ADD(OfficialSuite::playlist_noturi_attribution_location)
	TEST_ADD(OfficialSuite::playlist_noturi_extension)
	TEST_ADD(OfficialSuite::playlist_noturi_identifier)
	TEST_ADD(OfficialSuite::playlist_noturi_image)
	TEST_ADD(OfficialSuite::playlist_noturi_info)
	TEST_ADD(OfficialSuite::playlist_noturi_license)
	TEST_ADD(OfficialSuite::playlist_noturi_link_content)
	TEST_ADD(OfficialSuite::playlist_noturi_link_rel)
	TEST_ADD(OfficialSuite::playlist_noturi_location)
	TEST_ADD(OfficialSuite::playlist_noturi_meta)
	TEST_ADD(OfficialSuite::playlist_root_name)
	TEST_ADD(OfficialSuite::playlist_toomany_annotation)
	TEST_ADD(OfficialSuite::playlist_toomany_attribution)
	TEST_ADD(OfficialSuite::playlist_toomany_creator)
	TEST_ADD(OfficialSuite::playlist_toomany_date)
	TEST_ADD(OfficialSuite::playlist_toomany_identifier)
	TEST_ADD(OfficialSuite::playlist_toomany_image)
	TEST_ADD(OfficialSuite::playlist_toomany_info)
	TEST_ADD(OfficialSuite::playlist_toomany_license)
	TEST_ADD(OfficialSuite::playlist_toomany_location)
	TEST_ADD(OfficialSuite::playlist_toomany_title)
	TEST_ADD(OfficialSuite::playlist_toomany_tracklist)
	TEST_ADD(OfficialSuite::track_badint_duration)
	TEST_ADD(OfficialSuite::track_badint_tracknum)
	TEST_ADD(OfficialSuite::track_extension_application_missing)
	TEST_ADD(OfficialSuite::track_link_rel_missing)
	TEST_ADD(OfficialSuite::track_markup_album)
	TEST_ADD(OfficialSuite::track_markup_annotation)
	TEST_ADD(OfficialSuite::track_markup_creator)
	TEST_ADD(OfficialSuite::track_markup_meta)
	TEST_ADD(OfficialSuite::track_markup_title)
	TEST_ADD(OfficialSuite::track_meta_rel_missing)
	TEST_ADD(OfficialSuite::track_nonleaf_content)
	TEST_ADD(OfficialSuite::track_noturi_extension)
	TEST_ADD(OfficialSuite::track_noturi_identifier)
	TEST_ADD(OfficialSuite::track_noturi_image)
	TEST_ADD(OfficialSuite::track_noturi_info)
	TEST_ADD(OfficialSuite::track_noturi_link)
	TEST_ADD(OfficialSuite::track_noturi_link_rel)
	TEST_ADD(OfficialSuite::track_noturi_location)
	TEST_ADD(OfficialSuite::track_noturi_meta_rel)
	TEST_ADD(OfficialSuite::track_toomany_album)
	TEST_ADD(OfficialSuite::track_toomany_annotation)
	TEST_ADD(OfficialSuite::track_toomany_creator)
	TEST_ADD(OfficialSuite::track_toomany_duration)
	TEST_ADD(OfficialSuite::track_toomany_image)
	TEST_ADD(OfficialSuite::track_toomany_info)
	TEST_ADD(OfficialSuite::track_toomany_title)
	TEST_ADD(OfficialSuite::track_toomany_tracknum)
	TEST_ADD(OfficialSuite::track_whitespace_in_between)
	TEST_ADD(OfficialSuite::xml_error)

	// version 1 / pass
	TEST_ADD(OfficialSuite::playlist_empty_annotation)
	TEST_ADD(OfficialSuite::playlist_empty_creator)
	TEST_ADD(OfficialSuite::playlist_empty_meta)
	TEST_ADD(OfficialSuite::playlist_empty_title)
	TEST_ADD(OfficialSuite::playlist_extension)
	TEST_ADD(OfficialSuite::playlist_extensive)
	TEST_ADD(OfficialSuite::playlist_inverted_order)
	TEST_ADD(OfficialSuite::playlist_namespace_nested_proper)
	TEST_ADD(OfficialSuite::playlist_namespace_nondefault)
	TEST_ADD(OfficialSuite::playlist_namespace_two_additions)
	TEST_ADD(OfficialSuite::playlist_whitespace_dateTime)
	TEST_ADD(OfficialSuite::playlist_xml_base)
	TEST_ADD(OfficialSuite::track_empty_album)
	TEST_ADD(OfficialSuite::track_empty_annotation)
	TEST_ADD(OfficialSuite::track_empty_creator)
	TEST_ADD(OfficialSuite::track_empty_meta)
	TEST_ADD(OfficialSuite::track_empty_title)
	TEST_ADD(OfficialSuite::track_extension)
	TEST_ADD(OfficialSuite::track_extensive)
	TEST_ADD(OfficialSuite::track_inverted_order)
	TEST_ADD(OfficialSuite::track_whitespace_anyURI)
	TEST_ADD(OfficialSuite::track_whitespace_nonNegativeInteger)
}


class ErrorFishingCallback : public XspfReaderCallback {

	std::basic_string<XML_Char> firstErrorText;
	int firstErrorLine;
	bool strict;

public:
	ErrorFishingCallback(bool strict)
			: firstErrorText(), firstErrorLine(-1), strict(strict) {
	
	}

	XML_Char const * getErrorText() { return firstErrorText.c_str(); }
	int getErrorLine() { return firstErrorLine; }

	void notifyFatalError(int line, int column, int errorCode,
			XML_Char const * description) {
		firstErrorLine = line;
		firstErrorText.assign(description);
	}

	bool handleError(int line, int column, int errorCode,
			XML_Char const * description) {
		firstErrorLine = line;
		firstErrorText.assign(description);
		return !strict;
	}

};

void OfficialSuite::runCase(XML_Char const * filename, int expectedCode,
		bool skippable) {
	ErrorFishingCallback strictErrorFisherman(true);
	ErrorFishingCallback looseErrorFisherman(false);
	XML_Char const * const baseUri = _PT("http://www.example.org/");
	int const strictRes = this->reader.parseFile(
			filename, &strictErrorFisherman, baseUri);
	int const looseRes = this->reader.parseFile(
			filename, &looseErrorFisherman, baseUri);

	if (strictRes != expectedCode) {
		PORT_PRINTF(
				_PT("      File : %s\n")
				_PT("      Line : %i\n")
				_PT("Error text : '%s'\n")
				_PT("Error code : %i\n")
				_PT("  Expected : %i\n\n"),
				filename, strictErrorFisherman.getErrorLine(),
				strictErrorFisherman.getErrorText(),
				strictRes, expectedCode);
	}

	TEST_ASSERT(strictRes == expectedCode);

	if (skippable) {
		if (looseRes != XSPF_READER_SUCCESS) {
			PORT_PRINTF(
					_PT("      File : %s\n")
					_PT("      Line : %i\n")
					_PT("Error text : '%s'\n")
					_PT("Error code : %i\n")
					_PT("  Expected : %i\n\n"),
					filename, looseErrorFisherman.getErrorLine(),
					looseErrorFisherman.getErrorText(),
					looseRes, XSPF_READER_SUCCESS);
		}

		TEST_ASSERT(looseRes == XSPF_READER_SUCCESS);
	}
}


// version 0 / fail
void OfficialSuite::playlist_extension_forbidden() {
	runCase(V0_FAIL_PATH _PT("playlist-extension-forbidden.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::track_extension_forbidden() {
	runCase(V0_FAIL_PATH _PT("track-extension-forbidden.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::tracklist_no_tracks() {
	runCase(V0_FAIL_PATH _PT("tracklist-no-tracks.xspf"), XSPF_READER_ERROR_ELEMENT_MISSING);
}



// version 0 / pass
// none yet

// version 1 / fail
void OfficialSuite::playlist_attribute_forbidden_annotation() {
	runCase(V1_FAIL_PATH _PT("playlist-attribute-forbidden-annotation.xspf"), XSPF_READER_ERROR_ATTRIBUTE_FORBIDDEN);
}


void OfficialSuite::playlist_attribute_forbidden_playlist() {
	runCase(V1_FAIL_PATH _PT("playlist-attribute-forbidden-playlist.xspf"), XSPF_READER_ERROR_ATTRIBUTE_FORBIDDEN);
}


void OfficialSuite::playlist_baddate() {
	runCase(V1_FAIL_PATH _PT("playlist-baddate.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_badversion() {
	runCase(V1_FAIL_PATH _PT("playlist-badversion.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::playlist_element_forbidden_attribution() {
	runCase(V1_FAIL_PATH _PT("playlist-element-forbidden-attribution.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_extension_application_missing() {
	runCase(V1_FAIL_PATH _PT("playlist-extension-application-missing.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::playlist_link_rel_missing() {
	runCase(V1_FAIL_PATH _PT("playlist-link-rel-missing.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::playlist_markup_annotation() {
	runCase(V1_FAIL_PATH _PT("playlist-markup-annotation.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_markup_creator() {
	runCase(V1_FAIL_PATH _PT("playlist-markup-creator.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_markup_meta() {
	runCase(V1_FAIL_PATH _PT("playlist-markup-meta.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_markup_title() {
	runCase(V1_FAIL_PATH _PT("playlist-markup-title.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_meta_rel_missing() {
	runCase(V1_FAIL_PATH _PT("playlist-meta-rel-missing.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::playlist_missingtracklist() {
	runCase(V1_FAIL_PATH _PT("playlist-missingtracklist.xspf"), XSPF_READER_ERROR_ELEMENT_MISSING);
}


void OfficialSuite::playlist_missingversion() {
	runCase(V1_FAIL_PATH _PT("playlist-missingversion.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::playlist_namespace_missing() {
	runCase(V1_FAIL_PATH _PT("playlist-namespace-missing.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_namespace_nested_broken() {
	runCase(V1_FAIL_PATH _PT("playlist-namespace-nested-broken.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_namespace_wrong_string() {
	runCase(V1_FAIL_PATH _PT("playlist-namespace-wrong-string.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN, false);
}


void OfficialSuite::playlist_nonleaf_content_attribution() {
	runCase(V1_FAIL_PATH _PT("playlist-nonleaf-content-attribution.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_nonleaf_content_playlist() {
	runCase(V1_FAIL_PATH _PT("playlist-nonleaf-content-playlist.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_nonleaf_content_trackList() {
	runCase(V1_FAIL_PATH _PT("playlist-nonleaf-content-trackList.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_attribution_identifier() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-attribution-identifier.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_attribution_location() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-attribution-location.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_extension() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-extension.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::playlist_noturi_identifier() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-identifier.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_image() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-image.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_info() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-info.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_license() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-license.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_link_content() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-link-content.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_link_rel() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-link-rel.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::playlist_noturi_location() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-location.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::playlist_noturi_meta() {
	runCase(V1_FAIL_PATH _PT("playlist-noturi-meta.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::playlist_root_name() {
	runCase(V1_FAIL_PATH _PT("playlist-root-name.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::playlist_toomany_annotation() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-annotation.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_attribution() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-attribution.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_creator() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-creator.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_date() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-date.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_identifier() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-identifier.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_image() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-image.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_info() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-info.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_license() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-license.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_location() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-location.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_title() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-title.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::playlist_toomany_tracklist() {
	runCase(V1_FAIL_PATH _PT("playlist-toomany-tracklist.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_badint_duration() {
	runCase(V1_FAIL_PATH _PT("track-badint-duration.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_badint_tracknum() {
	runCase(V1_FAIL_PATH _PT("track-badint-tracknum.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_extension_application_missing() {
	runCase(V1_FAIL_PATH _PT("track-extension-application-missing.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::track_link_rel_missing() {
	runCase(V1_FAIL_PATH _PT("track-link-rel-missing.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::track_markup_album() {
	runCase(V1_FAIL_PATH _PT("track-markup-album.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::track_markup_annotation() {
	runCase(V1_FAIL_PATH _PT("track-markup-annotation.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::track_markup_creator() {
	runCase(V1_FAIL_PATH _PT("track-markup-creator.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::track_markup_meta() {
	runCase(V1_FAIL_PATH _PT("track-markup-meta.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::track_markup_title() {
	runCase(V1_FAIL_PATH _PT("track-markup-title.xspf"), XSPF_READER_ERROR_ELEMENT_FORBIDDEN);
}


void OfficialSuite::track_meta_rel_missing() {
	runCase(V1_FAIL_PATH _PT("track-meta-rel-missing.xspf"), XSPF_READER_ERROR_ATTRIBUTE_MISSING);
}


void OfficialSuite::track_nonleaf_content() {
	runCase(V1_FAIL_PATH _PT("track-nonleaf-content.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_noturi_extension() {
	runCase(V1_FAIL_PATH _PT("track-noturi-extension.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::track_noturi_identifier() {
	runCase(V1_FAIL_PATH _PT("track-noturi-identifier.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_noturi_image() {
	runCase(V1_FAIL_PATH _PT("track-noturi-image.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_noturi_info() {
	runCase(V1_FAIL_PATH _PT("track-noturi-info.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_noturi_link() {
	runCase(V1_FAIL_PATH _PT("track-noturi-link.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_noturi_link_rel() {
	runCase(V1_FAIL_PATH _PT("track-noturi-link-rel.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::track_noturi_location() {
	runCase(V1_FAIL_PATH _PT("track-noturi-location.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::track_noturi_meta_rel() {
	runCase(V1_FAIL_PATH _PT("track-noturi-meta-rel.xspf"), XSPF_READER_ERROR_ATTRIBUTE_INVALID);
}


void OfficialSuite::track_toomany_album() {
	runCase(V1_FAIL_PATH _PT("track-toomany-album.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_annotation() {
	runCase(V1_FAIL_PATH _PT("track-toomany-annotation.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_creator() {
	runCase(V1_FAIL_PATH _PT("track-toomany-creator.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_duration() {
	runCase(V1_FAIL_PATH _PT("track-toomany-duration.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_image() {
	runCase(V1_FAIL_PATH _PT("track-toomany-image.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_info() {
	runCase(V1_FAIL_PATH _PT("track-toomany-info.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_title() {
	runCase(V1_FAIL_PATH _PT("track-toomany-title.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_toomany_tracknum() {
	runCase(V1_FAIL_PATH _PT("track-toomany-tracknum.xspf"), XSPF_READER_ERROR_ELEMENT_TOOMANY);
}


void OfficialSuite::track_whitespace_in_between() {
	runCase(V1_FAIL_PATH _PT("track-whitespace-in-between.xspf"), XSPF_READER_ERROR_CONTENT_INVALID);
}


void OfficialSuite::xml_error() {
	runCase(V1_FAIL_PATH _PT("xml-error.xspf"), XSPF_READER_ERROR_EXPAT + XML_ERROR_DUPLICATE_ATTRIBUTE, false);
}



// version 1 / pass
void OfficialSuite::playlist_empty_annotation() {
	runCase(V1_PASS_PATH _PT("playlist-empty-annotation.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_empty_creator() {
	runCase(V1_PASS_PATH _PT("playlist-empty-creator.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_empty_meta() {
	runCase(V1_PASS_PATH _PT("playlist-empty-meta.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_empty_title() {
	runCase(V1_PASS_PATH _PT("playlist-empty-title.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_extension() {
	runCase(V1_PASS_PATH _PT("playlist-extension.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_extensive() {
	runCase(V1_PASS_PATH _PT("playlist-extensive.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_inverted_order() {
	runCase(V1_PASS_PATH _PT("playlist-inverted-order.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_namespace_nested_proper() {
	runCase(V1_PASS_PATH _PT("playlist-namespace-nested-proper.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_namespace_nondefault() {
	runCase(V1_PASS_PATH _PT("playlist-namespace-nondefault.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_namespace_two_additions() {
	runCase(V1_PASS_PATH _PT("playlist-namespace-two-additions.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_whitespace_dateTime() {
	runCase(V1_PASS_PATH _PT("playlist-whitespace-dateTime.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::playlist_xml_base() {
	runCase(V1_PASS_PATH _PT("playlist-xml-base.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_empty_album() {
	runCase(V1_PASS_PATH _PT("track-empty-album.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_empty_annotation() {
	runCase(V1_PASS_PATH _PT("track-empty-annotation.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_empty_creator() {
	runCase(V1_PASS_PATH _PT("track-empty-creator.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_empty_meta() {
	runCase(V1_PASS_PATH _PT("track-empty-meta.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_empty_title() {
	runCase(V1_PASS_PATH _PT("track-empty-title.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_extension() {
	runCase(V1_PASS_PATH _PT("track-extension.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_extensive() {
	runCase(V1_PASS_PATH _PT("track-extensive.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_inverted_order() {
	runCase(V1_PASS_PATH _PT("track-inverted-order.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_whitespace_anyURI() {
	runCase(V1_PASS_PATH _PT("track-whitespace-anyURI.xspf"), XSPF_READER_SUCCESS);
}


void OfficialSuite::track_whitespace_nonNegativeInteger() {
	runCase(V1_PASS_PATH _PT("track-whitespace-nonNegativeInteger.xspf"), XSPF_READER_SUCCESS);
}
