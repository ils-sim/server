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
#include <list>
#include <vector>
#include <string>

using namespace std;

#include <boost/shared_ptr.hpp>

#include "com_log/Log.h"
#include "CLI.h"

CLI_Command::CLI_Command(const string & cmdName, const string & description)
	: mCmdName(cmdName), mDescription(description)
{
}

string CLI_Command::GetCmdName() const
{
	return mCmdName;
}

void CLI_Command::PrintHelp() const
{
	Log::GetInstance()->Write("HELP   ", "Command: " + mCmdName);
	Log::GetInstance()->Write("HELP   ", "  " + mDescription);
}

int CLI_Command::GetInt(const string & name, std::istream & stream, const int default_)
{
	int value;
	cout << name << " (int): ";
	stream >> value;
	if(&stream != &std::cin)
	{
		cout << value << endl;
	}
	if(!CheckInput())
	{
		return default_;
	}
	return value;
}

double CLI_Command::GetDouble(const string & name, std::istream & stream, const double default_)
{
	double value;
	cout << name << " (double): ";
	stream >> value;
	if(&stream != &std::cin)
	{
		cout << value << endl;
	}
	if(!CheckInput())
	{
		return default_;
	}
	return value;
}

string CLI_Command::GetString(const string & name, std::istream & stream, const string & default_)
{
	string value;
	cout << name << " (string): ";
	stream >> value;
	if(&stream != &std::cin)
	{
		cout << value << endl;
	}
	if(!CheckInput())
	{
		return "";
	}
	return value;
}

bool CLI_Command::GetBool(const string & name, std::istream & stream, const bool default_)
{
	bool value;
	cout << name << " (bool): ";
	stream >> value;
	if(&stream != &std::cin)
	{
		cout << value << endl;
	}
	if(!CheckInput())
	{
		return default_;
	}
	return value;
}

bool CLI_Command::CheckInput()
{
	if(cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}


CLI::CLI()
{

}

void CLI::AddCommand(boost::shared_ptr<CLI_Command> cmd)
{
	mCommands.push_back(cmd);
}

bool CLI::Loop(std::istream & stream) const
{
	string line;
 	getline(stream, line);

	if(&stream != &std::cin)
	{
		Log::GetInstance()->Write("COMMAND", line);
	}

	if(line.find("#") != string::npos) // it's a comment
	{
		return true;
	}

	int pos = line.find(" ");
	string cmd;
	cmd = line.substr(0, pos);

	if(cmd == "exit")
	{
		return false;
	}
	if(cmd == "help")
	{
		PrintHelp();
		return true;
	}

	for(list<boost::shared_ptr<CLI_Command>>::const_iterator iter = mCommands.begin(); iter != mCommands.end(); ++iter)
	{
		if((*iter)->GetCmdName() == cmd)
		{
			(*iter)->Run(stream);
			return true;
		}
	}

	return true;
}

void CLI::PrintHelp() const
{
	for(list<boost::shared_ptr<CLI_Command>>::const_iterator iter = mCommands.begin(); iter != mCommands.end(); ++iter)
	{
		(*iter)->PrintHelp();
	}
}

