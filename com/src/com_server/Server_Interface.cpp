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
#include <string>
#include <stdint.h>

using namespace std;

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "com_convert/convert.h"
#include "com_log/Log.h"
#include "Client.h"
#include "Server_Interface.h"

Server_Observer::Server_Observer(Server_Interface * interface)
{
	mInterface = interface;
	interface->Attache(this);
}

Server_Interface * Server_Observer::GetInterface()
{
	return mInterface;
}


Server_Interface::Server_Interface()
{

}

void Server_Interface::Attache(Server_Observer * observer)
{
	mObservers.push_back(observer);
}

bool Server_Interface::Received_Package(Client & client, boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteDebug("Server_Interface::Received_Package");
	for(vector<Server_Observer*>::iterator iter = mObservers.begin(); iter != mObservers.end(); ++iter)
	{
		if(!(*iter)->Received_Package(client, pPackage))
		{
			return false;
		}
	}
	return true;
}
