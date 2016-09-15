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

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "com_log/Log.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "com_convert/convert.h"

#include "Vehicle_Status.h"
#include "TimeTable.h"
#include "Position.h"
#include "Route.h"
#include "Abstract_Vehicle.h"
#include "Vehicle_Amb.h"
#include "Hospital.h"


Vehicle_Ambulance::Vehicle_Ambulance(int Id, string Callsign, Point StationPosition)
	: Abstract_Vehicle(Id, Callsign, StationPosition, RTW)
{

}

void Vehicle_Ambulance::isStatusNichtEinsatzbereit()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusNichtEinsatzbereit: " + TToString(mId));
	mTimeTables.CalculateNext();
	setNextRuntime(mTimeTables.getNextActivity());
	mCurrentStatus = mTimeTables.getCarStatus();
	if(mCurrentStatus == Einsatzbereit && (mCurrentPosition.isZerro() || mCurrentPosition == mStationPoint))
	{
		mCurrentStatus = EintreffenDienststelle;
	}
	UpdateStatus();
}

void Vehicle_Ambulance::isStatusEintreffenDienststelle()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusEintreffenDienststelle: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mCurrentPosition = mStationPoint;
		mCurrentStatus = FahrzeugBesetzen;
		setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
		UpdateStatus();
	}
	else
	{
		mTimeTables.CalculateNext();
		setNextRuntime(mTimeTables.getNextActivity());
		UpdateStatus();
	}
}

void Vehicle_Ambulance::isStatusFahrzeugBesetzen()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusFahrzeugBesetzen: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mCurrentStatus = EinsatzAkzeptiert;
		UpdateStatus();
		mRoute.reset(new Route(Position(mCurrentPosition.GetLong(), mCurrentPosition.GetLat(), boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20)), mGoalPosition, KM_H2M_S(60)));
		mRoute->debug();
		setNextRuntime(mRoute->begin()->GetTimeAt());
	}
	else
	{
		mCurrentStatus = EintreffenDienststelle;
	}
}

void Vehicle_Ambulance::isStatusEinsatzbereit()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusEinsatzbereit: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		if(mCurrentPosition.isZerro())
		{
			mCurrentPosition = mStationPoint;
		}
		mCurrentStatus = EinsatzAkzeptiert;
		UpdateStatus();
		mRoute.reset(new Route(Position(mCurrentPosition.GetLong(), mCurrentPosition.GetLat(), boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20)), mGoalPosition, KM_H2M_S(60)));
		mRoute->debug();
		setNextRuntime(mRoute->begin()->GetTimeAt());
	}
	else
	{
		if(mCurrentPosition.isZerro())
		{
			mCurrentStatus = EintreffenDienststelle;
		}
		else
		{
			mCurrentStatus = AbfahrtZielort;
			setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
			mGoalPosition = mStationPoint;
			UpdateStatus();
			mRoute.reset(new Route(Position(mCurrentPosition.GetLong(), mCurrentPosition.GetLat(), getNextRuntime()), mStationPoint, KM_H2M_S(50)));
			mRoute->debug();
		}
	}
}

void Vehicle_Ambulance::isStatusEinsatzAkzeptiert()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusEinsatzAkzeptiert: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mCurrentPosition = (*mRoute->begin());
		mRoute->pop_front();
		UpdatePosition();
		if(mRoute->empty())
		{
			mCurrentStatus = AnkunftEinsatzort;
			setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
			UpdateStatus();
		}
		else
		{
			setNextRuntime(mRoute->begin()->GetTimeAt());
		}
	}
	else
	{
		mCurrentStatus = Einsatzbereit;
	}
}

void Vehicle_Ambulance::isStatusAnkunftEinsatzort()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusAnkunftEinsatzort: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mCurrentStatus = PatientGefunden;
		setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
		UpdateStatus();
	}
	else
	{
		Log::GetInstance()->WriteError("Vehicle_Ambulance::isStatusAnkunftEinsatzort: State should not be reached!");
	}
}

void Vehicle_Ambulance::isStatusPatientGefunden()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusPatientGefunden: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mCurrentStatus = AbfahrtEinsatzort;
		setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
		Hospital next_Hospital = Hospital_Cache::GetInstance()->searchClosestHospital(mCurrentPosition);
		mGoalPosition = next_Hospital.getPosition();
		UpdateStatus();
		mRoute.reset(new Route(Position(mCurrentPosition.GetLong(), mCurrentPosition.GetLat(), getNextRuntime()), mGoalPosition, KM_H2M_S(60)));
		mRoute->debug();
	}
	else
	{
		Log::GetInstance()->WriteError("Vehicle_Ambulance::isStatusAnkunftEinsatzort: State should not be reached!");
	}
}

void Vehicle_Ambulance::isStatusAbfahrtEinsatzort()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusAbfahrtEinsatzort: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mCurrentPosition = (*mRoute->begin());
		mRoute->pop_front();
		UpdatePosition();
		if(mRoute->empty())
		{
			mCurrentStatus = AnkunftZielort;
			setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
			UpdateStatus();
		}
		else
		{
			setNextRuntime(mRoute->begin()->GetTimeAt());
		}
	}
	else
	{
		Log::GetInstance()->WriteError("Vehicle_Ambulance::isStatusAnkunftEinsatzort: State should not be reached!");
	}
}

void Vehicle_Ambulance::isStatusAnkunftZielort()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusAnkunftZielort: " + TToString(mId));
	if(mEmergencyId != 0)
	{
		mEmergencyId = 0;
		mCurrentStatus = Einsatzbereit;
		setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(20));
		UpdateStatus();
	}
	else
	{
		Log::GetInstance()->WriteError("Vehicle_Ambulance::isStatusAnkunftEinsatzort: State should not be reached!");
	}
}

void Vehicle_Ambulance::isStatusAbfahrtZielort()
{
	Log::GetInstance()->WriteMessage("Vehicle_Ambulance::isStatusAbfahrtZielort: " + TToString(mId));
	mCurrentPosition = (*mRoute->begin());
	mRoute->pop_front();
	UpdatePosition();
	if(mRoute->empty())
	{
		mTimeTables.CalculateNext();
		setNextRuntime(mTimeTables.getNextActivity());
		mCurrentStatus = mTimeTables.getCarStatus();
		if(mCurrentStatus == Einsatzbereit)
		{
			mCurrentStatus = EintreffenDienststelle;
		}
		mEmergencyId = 0;
		mCurrentPosition.setZerro();
		UpdateStatus();
	}
	else
	{
		setNextRuntime(mRoute->begin()->GetTimeAt());
	}
}


