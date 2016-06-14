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
#include "com_log/Log.h"
#include "com_config/ini_reader.h"
#include "com_config/config.h"

#include "Observer.h"

Client * pClient;
boost::shared_ptr<ThreadSaveQueue<boost::shared_ptr<Task>>> inputQueue(new ThreadSaveQueue<boost::shared_ptr<Task>>);
bool mShutdown = false;

int main(int argc, char ** argv)
{
	if(argc == 2)
	{
		config::GetInstance()->readConfig(argv[1], "Einsatz");
		Log::GetInstance()->SetFileName(config::GetInstance()->getLogfile());
	}
	else
	{
		Log::GetInstance()->SetFileName("Einsatz.log");
	}
	Log::GetInstance()->ChangeSetting(config::GetInstance()->getLogSetting());
	Log::GetInstance()->EchoToConsole(config::GetInstance()->getLogEchoToConsole());
	Log::GetInstance()->WriteMessage("Start");

	boost::shared_ptr<SQL_ClientGlobalTask> mysql_task(new SQL_ClientGlobalTask()); 
	inputQueue->push(mysql_task);

	// Load data bevor sim... exactly hear!


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
		login->UID = config::GetInstance()->getEinsatzUID();
		login->Password = config::GetInstance()->getEinsatzPassword();
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
