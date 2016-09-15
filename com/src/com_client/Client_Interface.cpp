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
#include "com_client/Client_Interface.h"
#include "com_log/Log.h"

Client_Observer::Client_Observer(Client_Interface * interface)
{
	mInterface = interface;
	interface->Attache(this);
}

Client_Observer::~Client_Observer()
{
}

Client_Interface * Client_Observer::GetInterface()
{
	return mInterface;
}


Client_Interface::Client_Interface()
	: isConnected(NotConnected)
{
}

void Client_Interface::Attache(Client_Observer * observer)
{
	mObservers.push_back(observer);
}

void Client_Interface::Received_Package(boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteDebug("Client_Interface::Received_Package");
	for(vector<Client_Observer*>::iterator iter = mObservers.begin(); iter != mObservers.end(); ++iter)
	{
		(*iter)->Received_Package(pPackage);
	}
}

Client_Interface::~Client_Interface()
{
}
