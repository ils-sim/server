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

#include "com_convert/convert.h"
#include "com_server/Client.h"
#include "com_server/Server_Interface.h"
#include "com_server/Server.h"
#include "com_log/Log.h"

#include "Observer.h"

cServer_Observer::cServer_Observer(Server_Interface * interface)
	: Server_Observer(interface)
{
}

bool cServer_Observer::Received_Package(Client & client, boost::shared_ptr<Package> pPackage)
{
	switch(pPackage->GetType())
	{
	case Package::MSG_CHAT: // Just Server can send this, so disconnect the bad user ;)
	case Package::MSG_WALL:
	case Package::SERVER_WALL:
	case Package::MSG_PRIVATE:
	case Package::QUIT:
	case Package::USER_LIST_ANSWER:
	case Package::USER_LOGIN_ANSWER:
		return false;
		break;
	default:
		break;
	}
	return true;
}
