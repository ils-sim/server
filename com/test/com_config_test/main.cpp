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

#include "com_config/ini_reader.h"
#include "com_config/config.h"

void ini_test();

int main(int argc, char ** argv)
{
	ini_test();
}


void ini_test()
{
	Init_Reader reader("test.ini");

	cout << endl;
	cout << "Section: protocol" << endl;
	cout << "version: " << reader.getInteger("protocol", "version", -1) << endl;
	cout << endl;
	cout << "Section: user" << endl;
	cout << "name:   " << reader.getString("user", "name", "UNKNOWN") << endl;
	cout << "email:  " << reader.getString("user", "email", "UNKNOWN") << endl;
	cout << "pi:     " << reader.getFloat("user", "pi", -1) << endl;
	cout << "active: " << reader.getBoolean("user", "active", false) << endl;
}
