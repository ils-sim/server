/*********************************************************************************************
* 
* ILS-Sim.org Server
* Copyright (C) 2016  ils-sim.org Team
* 
* This program is free software; you can redistribute it and/or modify it under the terms
* of the GNU General Public License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with this
* program; if not, see <http://www.gnu.org/licenses/>.
* 
*********************************************************************************************/

#define BOOST_TEST_MODULE com_convert
#include <boost/test/included/unit_test.hpp>

using namespace std;

#include "com_convert/convert.h"

BOOST_AUTO_TEST_SUITE(Double_To_String)
BOOST_AUTO_TEST_CASE(Check_Null)
{
	BOOST_CHECK_EQUAL("0.0000000", DoubleToString(0.0));
}
BOOST_AUTO_TEST_CASE(Check_One)
{
	BOOST_CHECK_EQUAL("1.0000000", DoubleToString(1.0));
}
BOOST_AUTO_TEST_CASE(Check_Smale)
{
	BOOST_CHECK_EQUAL("0.2500000", DoubleToString(0.25));
}
BOOST_AUTO_TEST_CASE(Check_5)
{
	BOOST_CHECK_EQUAL("5.5550000", DoubleToString(5.555));
}
BOOST_AUTO_TEST_CASE(Check_M5)
{
	BOOST_CHECK_EQUAL("-5.5550000", DoubleToString(-5.555));
}
BOOST_AUTO_TEST_CASE(Check_MOne)
{
	BOOST_CHECK_EQUAL("-1.0000000", DoubleToString(-1.0));
}
BOOST_AUTO_TEST_SUITE_END()
