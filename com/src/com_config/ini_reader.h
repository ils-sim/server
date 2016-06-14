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

#ifndef INI_READER_H_
#define INI_READER_H_

class Init_Reader
{
public:
	Init_Reader();
	explicit Init_Reader(const string & filename);

	bool reload(const string & filename);

	int getInteger(const string & section, const string & key, const int default_value) const;
	float getFloat(const string & section, const string & key, const float default_value) const;
	bool getBoolean(const string & section, const string & key, const bool default_value) const;
	string getString(const string & section, const string & key, const string & default_value) const;

private:
	// section
	map<string, map<string, string>> mElements;

	static string::size_type find_char_or_comment(const string & str, const string & c);
};

#endif
