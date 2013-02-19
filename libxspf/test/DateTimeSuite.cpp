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

#include "DateTimeSuite.h"
#include <xspf/XspfToolbox.h>
using namespace Xspf;


void DateTimeSuite::normal_text(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("abc"), &dateTime));
}


void DateTimeSuite::combined(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("-2006-08-27T20:34:22.999+01:00"), &dateTime));
}


void DateTimeSuite::frac_1(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00.000000001-13:59"), &dateTime));
}


void DateTimeSuite::frac_2(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00.000000000-13:59"), &dateTime));
}


void DateTimeSuite::frac_3(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00.-13:59"), &dateTime));
}


void DateTimeSuite::shift_maximum_1(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00-13:59"), &dateTime));
}


void DateTimeSuite::shift_maximum_2(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00-14:00"), &dateTime));
}


void DateTimeSuite::shift_zero_zed(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00Z"), &dateTime));
}


void DateTimeSuite::shift_zero_lowercase(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00z"), &dateTime));
}


void DateTimeSuite::shift_zero_omitted(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01t00:00:00"), &dateTime));
}


void DateTimeSuite::all_maximum_2(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("9999-12-31T23:59:59+13:59"), &dateTime));
}


void DateTimeSuite::all_maximum_1(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("9999-12-31T23:59:59+14:00"), &dateTime));
}


void DateTimeSuite::year_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0000-01-01T00:00:00-13:59"), &dateTime));
}


void DateTimeSuite::month_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-00-01T00:00:00-13:59"), &dateTime));
}


void DateTimeSuite::day_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-00T00:00:00-13:59"), &dateTime));
}


void DateTimeSuite::hour_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T24:00:00-13:59"), &dateTime));
}


void DateTimeSuite::minute_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:60:00-13:59"), &dateTime));
}


void DateTimeSuite::second_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:60-13:59"), &dateTime));
}


void DateTimeSuite::shift_too_small(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00-14:01"), &dateTime));
}


void DateTimeSuite::shift_too_large(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("0001-01-01T00:00:00+14:01"), &dateTime));
}


void DateTimeSuite::leap_year_1(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("1600-02-29T00:00:00"), &dateTime));
}


void DateTimeSuite::leap_year_2(){
	TEST_ASSERT(XspfDateTime::extractDateTime(_PT("2004-02-29T00:00:00"), &dateTime));
}


void DateTimeSuite::leap_year_3(){
	TEST_ASSERT(!XspfDateTime::extractDateTime(_PT("1700-02-29T00:00:00"), &dateTime));
}
