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

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

#include <boost/shared_ptr.hpp>

#include "com_convert/convert.h"
#include "ini_reader.h"


Init_Reader::Init_Reader()
{
}

Init_Reader::Init_Reader(const string & filename)
{
	reload(filename);
}

bool Init_Reader::reload(const string & filename)
{
	string line = "";
	string currect_section = "";
	ifstream file(filename);
	if(!file.is_open())
	{
		cout << "unable to open file!" << endl;
		return false;
	}
	while(getline(file, line))
	{
		if(line == "") /* empty line */
		{
			continue;
		}
		line = trim_copy(line);
		if(line[0] == ';' || line[0] == '#') /* A comment line */
		{
			continue;
		}
		else if(line[0] == '[') /* A "[section]" line */
		{
			string::size_type pos = find_char_or_comment(line, "]");
			if(line[pos] == ']')
			{
				currect_section = line.substr(1, pos-1);
			}
			else
			{
				// no end found!
			}
		}
		else /* Not a comment or a section, must be a name[=:]value pair */
		{
			string::size_type pos = find_char_or_comment(line, "=");
			if(line[pos] != '=')
			{
				pos = find_char_or_comment(line, ":");
			}
			if(line[pos] == '=' || line[pos] == ':')
			{
				string name = line.substr(0, pos);
				string rest = line.substr(pos+1);
				pos = find_char_or_comment(rest, "");
				string value = rest.substr(0, pos);
				name = trim_copy(name);
				value = trim_copy(value);
				mElements[currect_section][name] = value;
			}
			else
			{
				// no data found... (empty line?)
			}
		}
	}
	file.close();
	return true;
}

int Init_Reader::getInteger(const string & section, const string & key, const int default_value) const
{
	map<string, map<string, string>>::const_iterator citer = mElements.find(section);
	if(citer == mElements.end())
	{
		return default_value;
	}
	map<string, string>::const_iterator citer2 = citer->second.find(key);
	if(citer2 == citer->second.end())
	{
		return default_value;
	}
	return StringToT<int>(citer2->second);
}

float Init_Reader::getFloat(const string & section, const string & key, const float default_value) const
{
	map<string, map<string, string>>::const_iterator citer = mElements.find(section);
	if(citer == mElements.end())
	{
		return default_value;
	}
	map<string, string>::const_iterator citer2 = citer->second.find(key);
	if(citer2 == citer->second.end())
	{
		return default_value;
	}
	return StringToT<float>(citer2->second);
}

bool Init_Reader::getBoolean(const string & section, const string & key, const bool default_value) const
{
	map<string, map<string, string>>::const_iterator citer = mElements.find(section);
	if(citer == mElements.end())
	{
		return default_value;
	}
	map<string, string>::const_iterator citer2 = citer->second.find(key);
	if(citer2 == citer->second.end())
	{
		return default_value;
	}
	if(citer2->second == "true" || citer2->second == "yes" || citer2->second == "on" || citer2->second == "1")
	{
		return true;
	}
	if(citer2->second == "false" || citer2->second == "no" || citer2->second == "off" || citer2->second == "0")
	{
		return false;
	}
	return default_value;
}

string Init_Reader::getString(const string & section, const string & key, const string & default_value) const
{
	map<string, map<string, string>>::const_iterator citer = mElements.find(section);
	if(citer == mElements.end())
	{
		return default_value;
	}
	map<string, string>::const_iterator citer2 = citer->second.find(key);
	if(citer2 == citer->second.end())
	{
		return default_value;
	}
	return citer2->second;
}

string::size_type Init_Reader::find_char_or_comment(const string & str, const string & c)
{
	string to_find = c + ";#";
	return str.find_first_of(to_find);
}

