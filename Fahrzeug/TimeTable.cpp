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

#include <list>

using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "com_convert/convert.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "com_log/Log.h"

#include "Vehicle_Status.h"
#include "TimeTable.h"
#include "Position.h"
#include "Route.h"
#include "Abstract_Vehicle.h"
#include "Hospital.h"
#include "Database.h"

static bool SortTimeTable(TimeEntry left, TimeEntry right);



TimeEntry::TimeEntry(boost::posix_time::time_duration start, boost::posix_time::time_duration end)
	: mStart(start), mEnd(end)
{

}

TimeEntry::TimeEntry(const int basis, const string & start, const string & end)
{
	mStart = MySQLTimeToTime_t(start) + boost::posix_time::seconds(basis);
	mEnd = MySQLTimeToTime_t(end) + boost::posix_time::seconds(basis);

	if(mEnd <= mStart)
	{
		mEnd += boost::posix_time::seconds(ONE_DAY);
	}

	// convert to utc for sumer time
	/*boost::local_time::local_date_time tloc = boost::local_time::local_sec_clock::local_time();
	if(tloc.is_dst())
	{*/
		mStart -= boost::posix_time::hours(2);
		mEnd -= boost::posix_time::hours(2);
	/*}
	else
	{
		mStart -= boost::posix_time::hours(1);
		mEnd -= boost::posix_time::hours(1);
	}*/
}

boost::posix_time::time_duration TimeEntry::getStart() const
{
	return mStart;
}

boost::posix_time::time_duration TimeEntry::getEnd() const
{
	return mEnd;
}

string TimeEntry::Print_duration(boost::posix_time::time_duration duration)
{
	stringstream ss;
	ss << "d: " << duration.hours() / 24 << " h: " << duration.hours() % 24;
	return ss.str();
}

void TimeEntry::Print() const
{
	cout << "  " << Print_duration(getStart()) << " - " << Print_duration(getEnd()) << endl;
}


TimeTable::TimeTable(int CarId)
	: mCarId(CarId), mNextStatus(NichtEinsatzbereit), mNextActivity(boost::posix_time::pos_infin)
{

}

void TimeTable::UpdateTable()
{
	mTable = TimeTableMapper::getTimeEntries(mCarId);
	mTable.sort(SortTimeTable);
}

void TimeTable::CalculateNext()
{
	Log::GetInstance()->WriteMessage("Check time status of Car (" + TToString(mCarId) + ").");
	boost::posix_time::ptime last_sunday = GetLastSunday();
	mNextActivity = boost::posix_time::pos_infin;

	if(mTable.empty())
	{
		Log::GetInstance()->WriteError("Car has no Timetable! idCar: " + TToString(mCarId));
		mNextActivity = last_sunday + boost::posix_time::seconds(ONE_WEEK);
		mNextStatus = NichtEinsatzbereit;
	}

	boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();

	for(list<TimeEntry>::iterator iter = mTable.begin(); iter != mTable.end(); ++iter)
	{
		if(((last_sunday + iter->getStart()) < now) && ((last_sunday + iter->getEnd()) < now)) // start and end are already in the past => shift is already done
		{
			//mNextActivity = last_sunday + iter->getStart();
			mNextStatus = NichtEinsatzbereit;
		}
		if(((last_sunday + iter->getStart()) > now ) && mNextActivity.is_pos_infinity()) // currently no shift assigned, and next shift is in the future
		{
			mNextActivity = last_sunday + iter->getStart();
			mNextStatus = NichtEinsatzbereit;
		}
		if(((last_sunday + iter->getStart()) < now) && ((last_sunday + iter->getEnd()) > now)) // start is in the past, end in the future => currently in shift
		{
			mNextActivity = last_sunday + iter->getEnd();
			mNextStatus = Einsatzbereit;
		}
	}
	if(mNextActivity.is_pos_infinity()) // next activity after current time?
	{
		Log::GetInstance()->WriteMessage("next activity service in next week. Car (" + TToString(mCarId) + ").");
		mNextActivity = last_sunday + boost::posix_time::seconds(ONE_WEEK) + mTable.begin()->getStart();
		mNextStatus = NichtEinsatzbereit;
	}
}

VehicleStatus TimeTable::getCarStatus() const
{
	return mNextStatus;
}

boost::posix_time::ptime TimeTable::getNextActivity() const
{
	return mNextActivity;
}

void TimeTable::Print() const
{
	cout << "ID: " << mCarId << endl;
	for(list<TimeEntry>::const_iterator iter = mTable.begin(); iter != mTable.end(); ++iter)
	{
		iter->Print();
	}
}


static bool SortTimeTable(TimeEntry left, TimeEntry right)
{
	return left.getStart() < right.getStart();
}

