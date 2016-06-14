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
#include "main.h"

Vehicle_Observer::Vehicle_Observer(Client_Interface * interface)
	: Client_Observer(interface)
{
}

void Vehicle_Observer::Received_Package(boost::shared_ptr<Package> pPackage)
{
	switch(pPackage->GetType())
	{
	case Package::VEHICLE_ALARM: // add Vehicle to Emergency
		{
			boost::shared_ptr<Vehicle_Alarm> alarm = boost::dynamic_pointer_cast<Vehicle_Alarm>(pPackage);
			AddCar2Emergency(alarm->IdEmergency, alarm->IdVehicle, alarm->BlueLight);
		}
		break;
	case Package::VEHICLE_STORNO: // remove a Vehicle from Emergency
		{
			boost::shared_ptr<Vehicle_Storno> alarm = boost::dynamic_pointer_cast<Vehicle_Storno>(pPackage);
			RemoveCarFromEmergency(alarm->IdEmergency, alarm->IdVehicle);
		}
		break;
	// not used because the will be send only!
	case Package::VEHICLE_UPDATE: // general Vehicle update
	case Package::VEHICLE_POSITION: // Position Update
	case Package::VEHICLE_MSG: // Msg. from Vehicle to CallingCenter
		break;
	default:
		break;
	}
}
