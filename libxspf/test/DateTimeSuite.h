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

#ifndef XSPF_TEST_DATE_TIME_SUITE_H
#define XSPF_TEST_DATE_TIME_SUITE_H 1


#include <cpptest.h>
#include <xspf/XspfDateTime.h>


class DateTimeSuite : public Test::Suite {

private:
	Xspf::XspfDateTime dateTime;

public:
	DateTimeSuite() {
		TEST_ADD(DateTimeSuite::normal_text)
		TEST_ADD(DateTimeSuite::combined)
		TEST_ADD(DateTimeSuite::frac_1)
		TEST_ADD(DateTimeSuite::frac_2)
		TEST_ADD(DateTimeSuite::frac_3)
		TEST_ADD(DateTimeSuite::shift_maximum_1)
		TEST_ADD(DateTimeSuite::shift_maximum_2)
		TEST_ADD(DateTimeSuite::shift_zero_zed)
		TEST_ADD(DateTimeSuite::shift_zero_lowercase)
		TEST_ADD(DateTimeSuite::shift_zero_omitted)
		TEST_ADD(DateTimeSuite::all_maximum_2)
		TEST_ADD(DateTimeSuite::all_maximum_1)
		TEST_ADD(DateTimeSuite::year_too_large)
		TEST_ADD(DateTimeSuite::month_too_large)
		TEST_ADD(DateTimeSuite::day_too_large)
		TEST_ADD(DateTimeSuite::hour_too_large)
		TEST_ADD(DateTimeSuite::minute_too_large)
		TEST_ADD(DateTimeSuite::second_too_large)
		TEST_ADD(DateTimeSuite::shift_too_small)
		TEST_ADD(DateTimeSuite::shift_too_large)
		TEST_ADD(DateTimeSuite::leap_year_1)
		TEST_ADD(DateTimeSuite::leap_year_2)
		TEST_ADD(DateTimeSuite::leap_year_3)
	}

private:
	void normal_text();
	void combined();
	void frac_1();
	void frac_2();
	void frac_3();
	void shift_maximum_1();
	void shift_maximum_2();
	void shift_zero_zed();
	void shift_zero_lowercase();
	void shift_zero_omitted();
	void all_maximum_2();
	void all_maximum_1();
	void year_too_large();
	void month_too_large();
	void day_too_large();
	void hour_too_large();
	void minute_too_large();
	void second_too_large();
	void shift_too_small();
	void shift_too_large();
	void leap_year_1();
	void leap_year_2();
	void leap_year_3();

};


#endif // XSPF_TEST_DATE_TIME_SUITE_H
