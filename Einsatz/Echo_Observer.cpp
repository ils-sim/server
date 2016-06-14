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

#include "Observer.h"

Echo_Observer::Echo_Observer(Client_Interface * interface)
	: Client_Observer(interface)
{
	mInt = 0;
}

void Echo_Observer::Received_Package(boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteMessage("Observer::Received_Package");
	Log::GetInstance()->WriteMessage(pPackage->Package2String());
	mInt++;
}
