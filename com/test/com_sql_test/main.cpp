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

using namespace std;

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "com_convert/convert.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "com_sql_client/SQL_Client.h"
#include "com_log/Log.h"

void read_land()
{
	boost::shared_ptr<SQL_Client> server = Generate_SQL_Client("new_ilssim");
	boost::shared_ptr<SQL_Result> result = server->SendQueryReturn("SELECT * FROM `Land`");

	while(result->next())
	{
		cout << "Index:  idLand: " << result->getInt(0) << ", Name: " << result->getString(1) << ", OSM: " << result->getInt(2) << endl;
		cout << "String: idLand: " << result->getInt("idLand") << ", Name: " << result->getString("Name") << ", OSM: " << result->getInt("osm") << endl;
	}
}

void read_fahrzeugstatus()
{
	boost::shared_ptr<SQL_Client> server = Generate_SQL_Client("online_ilssim");
	boost::shared_ptr<SQL_Result> result = server->SendQueryReturn("SELECT * FROM `FahrzeugStatus`");

	while(result->next())
	{
		cout << "Index:  idFahrzeugStatus: " << result->getInt(0) << ", Name: " << result->getString(1) << ", SystemStatus: " << result->getInt(2) << endl;
		cout << "String: idFahrzeugStatus: " << result->getInt("idFahrzeugStatus") << ", Name: " << result->getString("Name") << ", SystemStatus: " << result->getInt("SystemStatus") << endl;
	}
}


int main(int argc, char ** argv)
{
	read_fahrzeugstatus();
	read_land();

	return 0;
}


