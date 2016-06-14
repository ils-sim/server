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
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#include "com_convert/convert.h"
#include "com_client/Client_Interface.h"
#include "com_client/Client.h"
//#include "server/Client_Connection.h"
#include "com_server/Server_Interface.h"
#include "com_server/Server.h"
#include "com_log/Log.h"

class Observer : public Server_Observer
{
public:
	explicit Observer(Server_Interface * interface)
		: Server_Observer(interface)
	{
		mInt = 0;
	}

	virtual bool Received_Package(Client & client, boost::shared_ptr<Package> pPackage)
	{
		Log::GetInstance()->WriteMessage("Observer::Received_Package");
		Log::GetInstance()->WriteMessage(pPackage->Package2String());
		mInt++;
		return true;
	}

	int mInt;
};

int main(int argc, char ** argv)
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 1244);
	Server server(io_service, endpoint);

	Observer obs(&server);

	io_service.run();

	return 0;
}


