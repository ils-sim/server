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

#ifndef TIME_TABLE_H_
#define TIME_TABLE_H_

class TimeEntry
{
public:
	TimeEntry(int basis, string start, string end);
	TimeEntry(boost::posix_time::time_duration start, boost::posix_time::time_duration end);

	boost::posix_time::time_duration getStart() const;
	boost::posix_time::time_duration getEnd() const;

	void Print() const;
	static string Print_duration(boost::posix_time::time_duration duration);

private:
	boost::posix_time::time_duration mStart;
	boost::posix_time::time_duration mEnd;
};

class TimeTable
{
public:
	explicit TimeTable(int CarId);

	void UpdateTable();

	void CalculateNext();

	VehicleStatus getCarStatus() const;
	boost::posix_time::ptime getNextActivity() const;

	void Print() const;

private:
	list<TimeEntry> mTable;
	int mCarId;

	VehicleStatus mNextStatus;
	boost::posix_time::ptime mNextActivity;
};

#define ONE_DAY		(24*60*60)
#define ONE_WEEK	(7*ONE_DAY)
#define BASE_SO		(0)
#define BASE_MO		(BASE_SO + ONE_DAY)		// 86400
#define BASE_DI		(BASE_MO + ONE_DAY)		// 172800
#define BASE_MI		(BASE_DI + ONE_DAY)		// 259200
#define BASE_DO		(BASE_MI + ONE_DAY)		// 345600
#define BASE_FR		(BASE_DO + ONE_DAY)		// 432000
#define BASE_SA		(BASE_FR + ONE_DAY)		// 518400

#endif