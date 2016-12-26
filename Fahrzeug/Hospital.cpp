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

#include "com_task_scheduler/Task_Scheduler.h"

#include "Vehicle_Status.h"
#include "TimeTable.h"
#include "Position.h"
#include "Route.h"
#include "Abstract_Vehicle.h"
#include "Hospital.h"
#include "Database.h"


Hospital::Hospital(uint32_t id, const string & name, const Point & position)
	: mId(id), mName(name), mPosition(position)
{

}

//cppcheck-suppress unusedFunction
uint32_t Hospital::getId() const
{
	return mId;
}

//cppcheck-suppress unusedFunction
string Hospital::getName() const
{
	return mName;
}

Point Hospital::getPosition() const
{
	return mPosition;
}



Hospital Hospital_Cache::searchClosestHospital(Point position) const
{
	list<Hospital>::const_iterator selected = mHospitalList.begin();
	double selected_dist = Point::CalculateDistance(position, selected->getPosition());
	for(list<Hospital>::const_iterator iter = mHospitalList.begin(); iter != mHospitalList.end(); ++iter)
	{
		double iter_dist = Point::CalculateDistance(position, iter->getPosition());
		if(iter_dist < selected_dist)
		{
			selected_dist = iter_dist;
			selected = iter;
		}
	}
	return *selected;
}

Hospital_Cache::Hospital_Cache()
	: mHospitalList(HospitalMapper::getAll())
{
}

Hospital_Cache::~Hospital_Cache()
{

}
