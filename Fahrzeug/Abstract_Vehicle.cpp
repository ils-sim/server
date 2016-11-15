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
#include <string>
#include <list>

using namespace std;

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;

#include "com_log/Log.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "com_convert/convert.h"
#include "com_client/Client_Interface.h"
#include "com_client/Client.h"

#include "Vehicle_Status.h"
#include "TimeTable.h"
#include "Position.h"
#include "Route.h"
#include "Abstract_Vehicle.h"
#include "Hospital.h"
#include "Database.h"
#include "main.h"

#define CAR_SPEED	(70.0 / 3.6) // in m/s


Abstract_Vehicle::Abstract_Vehicle(uint32_t Id, const string & Callsign, const Point & StationPosition, VehicleType type)
	: Task(RunnerPrio, Callsign), mId(Id), mCallsign(Callsign), mStationPoint(StationPosition), mCarType(type), mTimeTables(mId), mCurrentStatus(NichtEinsatzbereit)
{
	mEmergencyId = 0;
	mIsBlue = false;
	mPatientId = 0;
	mTimeTables.UpdateTable();
	mTimeTables.CalculateNext();
	setNextRuntime(mTimeTables.getNextActivity());
	mCurrentStatus = mTimeTables.getCarStatus();
	if(mCurrentStatus != NichtEinsatzbereit)
	{
		mCurrentStatus = VehicleMapper::getLastStatus(mId);
	}
}

//cppcheck-suppress unusedFunction
void Abstract_Vehicle::AddToEmergency(uint64_t emergency, bool isBlue, Point position)
{
	if(mCurrentStatus != NichtEinsatzbereit)
	{
		Log::GetInstance()->WriteMessage("Adding Emergency (" + TToString(emergency) + ") to Car (" + TToString(mId) + ").");
		mEmergencyId = emergency;
		mIsBlue = isBlue;
		setNextRuntime(boost::posix_time::neg_infin);
		mGoalPosition = position;
	}
	else
	{
		Log::GetInstance()->WriteWarning("Can not add Car (" + TToString(mId) + ") to Emergency (" + TToString(emergency) + ")! Because Car is not 'Einsatzbereit'!");
	}
}

//cppcheck-suppress unusedFunction
void Abstract_Vehicle::RemoveFromEmergency()
{
	mEmergencyId = 0;
	mIsBlue = 0;
	mTimeTables.CalculateNext();
	setNextRuntime(mTimeTables.getNextActivity());
}

//cppcheck-suppress unusedFunction
int Abstract_Vehicle::GetId() const
{
	return mId;
}

//cppcheck-suppress unusedFunction
string Abstract_Vehicle::GetCallsign() const
{
	return mCallsign;
}

//cppcheck-suppress unusedFunction
Point Abstract_Vehicle::GetCurrentPosition() const
{
	return mCurrentPosition;
}

VehicleType Abstract_Vehicle::GetType() const
{
	return mCarType;
}

//cppcheck-suppress unusedFunction
VehicleStatus Abstract_Vehicle::GetStatus() const
{
	return mCurrentStatus;
}

//cppcheck-suppress unusedFunction
void Abstract_Vehicle::PrintCar() const
{
	cout << "Car             : " << mId << endl;
	cout << "  name          : " << mCallsign << endl;
	cout << "  status        : " << VehicleStatus2String(mCurrentStatus) << endl;
	cout << "  emergency ID  : " << mEmergencyId << endl;
	cout << "  blue light    : " << mIsBlue << endl;
	cout << "  NextActivity  : " << to_simple_string(mTimeTables.getNextActivity()) << endl;
	cout << "  CurrentPoint  : " << mCurrentPosition.Print() << endl;;
	cout << "  GoalPoint     : " << mGoalPosition.Print() << endl;
	cout << "  StationPoint  : " << mStationPoint.Print() << endl;
}

void Abstract_Vehicle::UpdatePosition()
{
	Log::GetInstance()->WriteMessage("Abstract_Vehicle::UpdatePosition: mCurrentPosition: " + mCurrentPosition.Print());

	VehicleMapper::UpdatePosition(mId, mCurrentPosition);

	// send to Sync server!
	boost::shared_ptr<Vehicle_Position> update(new Vehicle_Position());
	update->IdVehicle = mId;
	update->Latitude = mCurrentPosition.GetLat();
	update->Longitude = mCurrentPosition.GetLong();
	SendPackage(update);
}

void Abstract_Vehicle::UpdateStatus()
{
	Log::GetInstance()->WriteMessage("Abstract_Vehicle::UpdateStatus: mCurrentStatus: " + VehicleStatus2String(mCurrentStatus));
	VehicleMapper::UpdateStatus(mId, mCurrentStatus, mGoalPosition, mEmergencyId, mPatientId, mIsBlue);
	
	// send to Sync server!
	boost::shared_ptr<Vehicle_Update> update(new Vehicle_Update());
	update->IdVehicle = mId;
	update->Status = (Vehicle_Update::VehicleStatus)mCurrentStatus;
	update->DestinationLatitude = mGoalPosition.GetLat();
	update->DestinationLongitude = mGoalPosition.GetLong();
	update->IdEmergency = mEmergencyId;
	update->IdPatient = mPatientId;
	update->BlueLight = mIsBlue;
	SendPackage(update);
}

void Abstract_Vehicle::run()
{
	Log::GetInstance()->WriteDebug("Abstract_Vehicle::run: " + TToString(mId));

	switch (mCurrentStatus)
	{
	case Einsatzbereit:
		isStatusEinsatzbereit();
		break;
	case EintreffenDienststelle:
		isStatusEintreffenDienststelle();
		break;
	case FahrzeugBesetzen:
		isStatusFahrzeugBesetzen();
		break;
	case EinsatzAkzeptiert:
		isStatusEinsatzAkzeptiert();
		break;
	case AnkunftEinsatzort:
		isStatusAnkunftEinsatzort();
		break;
	case PatientGefunden:
		isStatusPatientGefunden();
		break;
	case AbfahrtEinsatzort:
		isStatusAbfahrtEinsatzort();
		break;
	case AnkunftZielort:
		isStatusAnkunftZielort();
		break;
	case AbfahrtZielort:
		isStatusAbfahrtZielort();
		break;
	case NichtEinsatzbereit:
		isStatusNichtEinsatzbereit();
		break;
	default:
		Log::GetInstance()->WriteError("Abstract_Vehicle::run: Not known status: " + VehicleStatus2String(mCurrentStatus));
		break;
	}
	Log::GetInstance()->WriteMessage("Abstract_Vehicle::run: NEW STATUS: " + VehicleStatus2String(mCurrentStatus));

	/*if(mCurrentStatus == NichtEinsatzbereit)
	{
		Log::GetInstance()->WriteDebug("Abstract_Vehicle::run: Looking for next activity...");
		mTimeTables.CalculateNext();
		setNextRuntime(mTimeTables.getNextActivity());
		mCurrentStatus = mTimeTables.getCarStatus();
		UpdateStatus();
	}*/
}

