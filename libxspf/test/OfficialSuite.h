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

#ifndef XSPF_TEST_OFFICIAL_SUITE_H
#define XSPF_TEST_OFFICIAL_SUITE_H 1


#include <cpptest.h>
#include <xspf/XspfReader.h>


class OfficialSuite : public Test::Suite {

private:
	Xspf::XspfReader reader;

public:
	OfficialSuite();

private:
	void runCase(XML_Char const * filename, int expectedCode,
		bool skippable = true);

	// version 0 / fail
	void playlist_extension_forbidden();
	void track_extension_forbidden();
	void tracklist_no_tracks();

	// version 0 / pass
	// none yet

	// version 1 / fail
	void playlist_attribute_forbidden_annotation();
	void playlist_attribute_forbidden_playlist();
	void playlist_baddate();
	void playlist_badversion();
	void playlist_element_forbidden_attribution();
	void playlist_extension_application_missing();
	void playlist_link_rel_missing();
	void playlist_markup_annotation();
	void playlist_markup_creator();
	void playlist_markup_meta();
	void playlist_markup_title();
	void playlist_meta_rel_missing();
	void playlist_missingtracklist();
	void playlist_missingversion();
	void playlist_namespace_missing();
	void playlist_namespace_nested_broken();
	void playlist_namespace_wrong_string();
	void playlist_nonleaf_content_attribution();
	void playlist_nonleaf_content_playlist();
	void playlist_nonleaf_content_trackList();
	void playlist_noturi_attribution_identifier();
	void playlist_noturi_attribution_location();
	void playlist_noturi_extension();
	void playlist_noturi_identifier();
	void playlist_noturi_image();
	void playlist_noturi_info();
	void playlist_noturi_license();
	void playlist_noturi_link_content();
	void playlist_noturi_link_rel();
	void playlist_noturi_location();
	void playlist_noturi_meta();
	void playlist_root_name();
	void playlist_toomany_annotation();
	void playlist_toomany_attribution();
	void playlist_toomany_creator();
	void playlist_toomany_date();
	void playlist_toomany_identifier();
	void playlist_toomany_image();
	void playlist_toomany_info();
	void playlist_toomany_license();
	void playlist_toomany_location();
	void playlist_toomany_title();
	void playlist_toomany_tracklist();
	void track_badint_duration();
	void track_badint_tracknum();
	void track_extension_application_missing();
	void track_link_rel_missing();
	void track_markup_album();
	void track_markup_annotation();
	void track_markup_creator();
	void track_markup_meta();
	void track_markup_title();
	void track_meta_rel_missing();
	void track_nonleaf_content();
	void track_noturi_extension();
	void track_noturi_identifier();
	void track_noturi_image();
	void track_noturi_info();
	void track_noturi_link();
	void track_noturi_link_rel();
	void track_noturi_location();
	void track_noturi_meta_rel();
	void track_toomany_album();
	void track_toomany_annotation();
	void track_toomany_creator();
	void track_toomany_duration();
	void track_toomany_image();
	void track_toomany_info();
	void track_toomany_title();
	void track_toomany_tracknum();
	void track_whitespace_in_between();
	void xml_error();

	// version 1 / pass
	void playlist_empty_annotation();
	void playlist_empty_creator();
	void playlist_empty_meta();
	void playlist_empty_title();
	void playlist_extension();
	void playlist_extensive();
	void playlist_inverted_order();
	void playlist_namespace_nested_proper();
	void playlist_namespace_nondefault();
	void playlist_namespace_two_additions();
	void playlist_whitespace_dateTime();
	void playlist_xml_base();
	void track_empty_album();
	void track_empty_annotation();
	void track_empty_creator();
	void track_empty_meta();
	void track_empty_title();
	void track_extension();
	void track_extensive();
	void track_inverted_order();
	void track_whitespace_anyURI();
	void track_whitespace_nonNegativeInteger();

};


#endif // XSPF_TEST_OFFICIAL_SUITE_H
