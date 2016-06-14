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

#ifndef CONVERT_H_
#define CONVERT_H_

#include <string>
#include <sstream>
#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>
#if __WIN32__ || _MSC_VER
	#pragma warning( disable : 4996 )
#endif

template<typename T>
T StringToT(string str)
{
	stringstream ss(str);
	T i;
	ss >> i;
	return i;
}

template<typename T>
string TToString(T i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

wstring StringToWString(const string & s);
string WStringToString(const wstring & s);

boost::posix_time::ptime GetLastSunday();
boost::posix_time::time_duration MySQLTimeToTime_t(const string & time);
string Time_ttoMySQLTime(const boost::posix_time::ptime & time);

string DoubleToString(const double d);

string trim_right_copy(const string & s, const string & delimiters = " \f\n\r\t\v");
string trim_left_copy(const string & s, const string & delimiters = " \f\n\r\t\v");
string trim_copy(const string & s, const string & delimiters = " \f\n\r\t\v");

#define UNUSED(x) (void)(x)

#endif
