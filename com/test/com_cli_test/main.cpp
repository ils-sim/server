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
#include <vector>
#include <list>
#include <string>

using namespace std;

#include <boost/shared_ptr.hpp>

#include "com_cli/CLI.h"

class Test_Cmd : public CLI_Command
{
public:
	Test_Cmd()
		: CLI_Command("test", "Test Command.")
	{}

	virtual void Run(std::istream & stream)
	{
		cout << "RUUUUNNNN" << endl;
		
		string str_ = GetString("String", stream);
		int int_ = GetInt("Int", stream);
		double double_ = GetDouble("double", stream);

		cout << "str: " << str_ << endl;
		cout << "int: " << int_ << endl;
		cout << "double: " << double_ << endl;
	}
};

int main(int argc, char ** argv)
{
	boost::shared_ptr<Test_Cmd> test(new Test_Cmd);
	CLI cli;
	cli.AddCommand(test);
	cli.PrintHelp();

	while(cli.Loop(cin))
	{

	}
}
