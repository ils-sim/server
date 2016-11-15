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

using namespace std;

#include <boost/asio.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

#include "protocol.pb.h"
#include "com_convert/convert.h"
#include "com_client/Client_Interface.h"
#include "com_client/Client.h"
#include "com_log/Log.h"

#include "com_cli/CLI.h"


Client * pClient;

#include "client_cmds.h"
#include "from_client_cmds.h"
#include "from_server_cmds.h"

class Observer : public Client_Observer
{
public:
	explicit Observer(Client_Interface * interface)
		: Client_Observer(interface)
	{
		mInt = 0;
	}

	virtual void Received_Package(boost::shared_ptr<Package> pPackage)
	{
		Log::GetInstance()->WriteMessage("Observer::Received_Package");
		Log::GetInstance()->WriteMessage(pPackage->Package2String());
		mInt++;
	}

	int mInt;
};

#define AddCMD(cmd) cli.AddCommand(boost::shared_ptr<cmd>(new cmd))

int main(int argc, char ** argv)
{
	Log::GetInstance()->SetFileName("client_test.log");
#ifdef _DEBUG
	Log::GetInstance()->ChangeSetting(Log::LogDebug);
#endif

	try
	{
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query("127.0.0.1", "1244");
		tcp::resolver::iterator iterator = resolver.resolve(query);


		pClient = new Client(io_service, iterator);
		Observer obs(pClient);

		boost::thread runner(boost::bind(&boost::asio::io_service::run, &io_service));

		CLI cli;
		AddCMD(UserLogin_Cmd);
		AddCMD(UserLogout_Cmd);
		AddCMD(UserWall_Cmd);
		AddCMD(UserChat_Cmd);
		AddCMD(UserMsg_Cmd);
		AddCMD(UserList_Cmd);
		AddCMD(CallAccept_Cmd);
		AddCMD(CallAccept_Cmd);
		AddCMD(VehicleAlarm_Cmd);
		AddCMD(VehicleStorno_Cmd);

		AddCMD(EmergNew_Cmd);
		AddCMD(EmergUpdate_Cmd);
		AddCMD(EmergEnd_Cmd);
		AddCMD(CaseNew_Cmd);
		AddCMD(CaseUpdate_Cmd);
		AddCMD(CaseEnd_Cmd);
		AddCMD(VehicleMsg_Cmd);
		AddCMD(VehicleUpdate_Cmd);
		AddCMD(VehiclePosition_Cmd);
		AddCMD(CallAccepted_Cmd);
		AddCMD(MsgWall_Cmd);
		AddCMD(MsgChat_Cmd);
		AddCMD(MsgPrivate_Cmd);
		AddCMD(ServerWall_Cmd);
		AddCMD(UserLoginAnswer_Cmd);
		AddCMD(UserListAnswer_Cmd);
		AddCMD(Quit_Cmd);

		LoadScript_Cmd * ScriptLoader = new LoadScript_Cmd(&cli);
		cli.AddCommand(boost::shared_ptr<LoadScript_Cmd>(ScriptLoader));
		AddCMD(Sleep_Cmd);

		if(argc >= 2)
		{
			Log::GetInstance()->WriteMessage("Set script path to: " + TToString(argv[1]));
			ScriptLoader->SetPath(argv[1]);
		}

		// wait for connection
		while(pClient->isConnected == NotConnected);
		if(pClient->isConnected == Error)
		{
			pClient->Close();
			runner.join();
			delete pClient;
			return 1;
		}

		if(argc <= 2)
		{
			Log::GetInstance()->WriteMessage("Console mode:");
			while(cli.Loop(cin)) {}
		}
		else
		{
			Log::GetInstance()->WriteMessage("execute script files:");
			for (int i = 2; i < argc; i++)
			{
				Log::GetInstance()->WriteMessage("[" + TToString(i) + "]: " + argv[i]);
				ScriptLoader->RunScript(argv[i]);
			}
		}
		Log::GetInstance()->WriteMessage("No stuff to do, closing connection");
		Log::GetInstance()->WritePanic("Panic - remove me, when you use this function finaly somwhere else!");

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
