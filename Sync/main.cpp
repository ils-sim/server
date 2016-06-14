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
#include <map>

using namespace std;

#include "protocol.pb.h"

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "com_convert/convert.h"
#include "com_server/Client.h"
#include "com_server/Server_Interface.h"
#include "com_server/Server.h"
#include "com_log/Log.h"
#include "com_config/ini_reader.h"
#include "com_config/config.h"

#include "Observer.h"

int main(int argc, char ** argv)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if(argc == 2)
	{
		config::GetInstance()->readConfig(argv[1], "Sync");
		Log::GetInstance()->SetFileName(config::GetInstance()->getLogfile());
	}
	else
	{
		Log::GetInstance()->SetFileName("Sync.log");
	}
	Log::GetInstance()->ChangeSetting(config::GetInstance()->getLogSetting());
	Log::GetInstance()->EchoToConsole(config::GetInstance()->getLogEchoToConsole());
	Log::GetInstance()->WriteMessage("Start");

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), config::GetInstance()->getTCPPort());
	Server server(io_service, endpoint);

	Echo_Observer echo_obs(&server);
	Emergencies_Observer emergencies_obs(&server);
	cServer_Observer server_obs(&server);
	User_Observer user_obs(&server);
	Vehicle_Observer vehicle_obs(&server);

	io_service.run();

	return 0;
}


