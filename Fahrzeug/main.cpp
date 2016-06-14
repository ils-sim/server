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
#include <map>

using namespace std;

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;

#include "protocol.pb.h"
#include "com_convert/convert.h"
#include "com_log/Log.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "com_sql_client/SQL_Client.h"
#include "com_client/Client_Interface.h"
#include "com_client/Client.h"
#include "com_config/ini_reader.h"
#include "com_config/config.h"

#include "Observer.h"

#include "Vehicle_Status.h"
#include "Position.h"
#include "TimeTable.h"
#include "Route.h"
#include "Abstract_Vehicle.h"
#include "Vehicle_Amb.h"
#include "Hospital.h"
#include "Database.h"
#include "main.h"

Client * pClient;
boost::shared_ptr<ThreadSaveQueue<boost::shared_ptr<Task>>> inputQueue(new ThreadSaveQueue<boost::shared_ptr<Task>>);
list<boost::shared_ptr<Abstract_Vehicle>> CarList;
bool mShutdown = false;

void LoadDataFromMySQL();

int main(int argc, char ** argv)
{
	if(argc == 2)
	{
		config::GetInstance()->readConfig(argv[1], "Fahrzeug");
		Log::GetInstance()->SetFileName(config::GetInstance()->getLogfile());
	}
	else
	{
		Log::GetInstance()->SetFileName("Fahrzeug.log");
	}
	Log::GetInstance()->ChangeSetting(config::GetInstance()->getLogSetting());
	Log::GetInstance()->EchoToConsole(config::GetInstance()->getLogEchoToConsole());
	Log::GetInstance()->WriteMessage("Start");

	boost::shared_ptr<SQL_ClientGlobalTask> mysql_task(new SQL_ClientGlobalTask()); 
	inputQueue->push(mysql_task);

	LoadDataFromMySQL();

	/*cout << "*******************************************" << endl
		 << "**          NICHT Einsatzbereit          **" << endl
		 << "*******************************************" << endl;
	for(list<boost::shared_ptr<Abstract_Vehicle>>::const_iterator iter = CarList.begin(); iter != CarList.end(); ++iter)
	{
		if((*iter)->GetStatus() == NichtEinsatzbereit)
		{
			(*iter)->PrintCar();
		}
	}

	cout << "*******************************************" << endl
		 << "**             Einsatzbereit             **" << endl
		 << "*******************************************" << endl;
	for(list<boost::shared_ptr<Abstract_Vehicle>>::const_iterator iter = CarList.begin(); iter != CarList.end(); ++iter)
	{
		if((*iter)->GetStatus() != NichtEinsatzbereit)
		{
			(*iter)->PrintCar();
		}
	}*/

	TaskScheduler Scheduler(inputQueue);

	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query("127.0.0.1", TToString(config::GetInstance()->getTCPPort()));
		tcp::resolver::iterator iterator = resolver.resolve(query);


		pClient = new Client(io_service, iterator);
		Echo_Observer echo_obs(pClient);
		Emergencies_Observer emergencies_obs(pClient);
		cServer_Observer server_obs(pClient);
		User_Observer user_obs(pClient);
		Vehicle_Observer vehicle_obs(pClient);

		boost::thread runner(boost::bind(&boost::asio::io_service::run, &io_service));

		while(pClient->isConnected == NotConnected);
		if(pClient->isConnected == Error)
		{
			pClient->Close();
			runner.join();
			delete pClient;
			return 1;
		}

		boost::shared_ptr<User_Login> login(new User_Login());
		login->ControlCenter = 0;
		login->UID = config::GetInstance()->getFahrzeugUID();
		login->Password = config::GetInstance()->getFahrzeugPassword();
		pClient->Send(login);

		while(!mShutdown)
		{
			Scheduler.Run();
		}

		cout << "Press [ENTER] to exit" << endl;
		string str;
		cin >> str;


		pClient->Close();
		runner.join();
		delete pClient;
	}
	catch (exception & e)
	{
		Log::GetInstance()->WriteError(e.what());
	}

	return 0;
}

void LoadDataFromMySQL()
{
	CarList = VehicleMapper::getAll();
	for(list<boost::shared_ptr<Abstract_Vehicle>>::const_iterator iter = CarList.begin(); iter != CarList.end(); ++iter)
	{
		inputQueue->push(*iter);
	}
}

void Shutdown()
{
	mShutdown = true;
}

void AddCar2Emergency(uint64_t idEmergency, int32_t IdVehicle, bool BlueLight)
{
	Point point = EmergencyMapper::GetEmergencyPoint(idEmergency);
	if(point.isZerro())
	{
		return;
	}
	for(list<boost::shared_ptr<Abstract_Vehicle>>::const_iterator iter = CarList.begin(); iter != CarList.end(); ++iter)
	{
		if((*iter)->GetId() == IdVehicle)
		{
			if((*iter)->GetStatus() == Einsatzbereit || (*iter)->GetStatus() == AbfahrtZielort || (*iter)->GetStatus() == EintreffenDienststelle)
			{
				(*iter)->AddToEmergency(idEmergency, BlueLight, point);
			}
			else
			{
				Log::GetInstance()->WriteWarning("Vehicle (" + TToString((*iter)->GetId()) + ") is not ready to go on a new mission! Current Status: " + VehicleStatus2String((*iter)->GetStatus()));
			}
			(*iter)->PrintCar();
		}
	}
}

void RemoveCarFromEmergency(uint64_t idEmergency, int32_t IdVehicle)
{
	for(list<boost::shared_ptr<Abstract_Vehicle>>::const_iterator iter = CarList.begin(); iter != CarList.end(); ++iter)
	{
		if((*iter)->GetId() == IdVehicle)
		{
			(*iter)->RemoveFromEmergency();
			(*iter)->PrintCar();
		}
	}
}

void SendPackage(boost::shared_ptr<Package> pPackage)
{
	pClient->Send(pPackage);
}
