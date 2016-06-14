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

#include <sstream>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using namespace std;

#include "convert.h"

boost::posix_time::ptime GetLastSunday()
{
	boost::posix_time::ptime now(boost::posix_time::microsec_clock::universal_time());
	tm t = to_tm(now);

	now -= boost::posix_time::hours(t.tm_wday * 24);
	now -= boost::posix_time::hours(t.tm_hour);
	now -= boost::posix_time::minutes(t.tm_min);
	now -= boost::posix_time::seconds(t.tm_sec);

	//struct tm * tm = localtime(&now);
	//cout << tm->tm_mday << '.' << tm->tm_mon << '.' << (1900 + tm->tm_year)
	//	<< ' ' << tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec << " : " << endl;
	return now;
}

// hh:mm:ss
boost::posix_time::time_duration MySQLTimeToTime_t(const string & time)
{
	char num[5];
	char const * str = time.c_str();

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	int hour_ = static_cast<int>(strtol(num, 0, 10));
	if (*str == ':') str++;

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	int minute_ = static_cast<int>(strtol(num, 0, 10));
	if (*str == ':') str++;

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	int second_ = static_cast<int>(strtol(num, 0, 10));

	boost::posix_time::time_duration new_time;

	new_time += boost::posix_time::hours(hour_);
	new_time += boost::posix_time::minutes(minute_);
	new_time += boost::posix_time::seconds(second_);

	return new_time;
}

string Time_ttoMySQLTime(const boost::posix_time::ptime & time)
{
	boost::posix_time::time_facet * facet = new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S");
	stringstream stream;
	stream.imbue(locale(stream.getloc(), facet));
	stream << time;
	return stream.str();
}

//cppcheck-suppress unusedFunction
wstring StringToWString(const string & s)
{
    wstring wsTmp(s.begin(), s.end());
	return wsTmp;
}

//cppcheck-suppress unusedFunction
string WStringToString(const wstring & s)
{
	string wsTmp(s.begin(), s.end());
	return wsTmp;
}

string DoubleToString(const double d)
{
	stringstream ss;
	ss.precision(7);
	ss << fixed << d;
	return ss.str();
}


string trim_right_copy(const string & s, const string & delimiters)
{
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

string trim_left_copy(const string & s, const string & delimiters)
{
	return s.substr(s.find_first_not_of(delimiters));
}

string trim_copy(const string & s, const string & delimiters)
{
	return trim_left_copy(trim_right_copy(s, delimiters), delimiters);
}


