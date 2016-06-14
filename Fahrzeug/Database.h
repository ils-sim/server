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

#ifndef DATABASE_H_
#define DATABASE_H_

class VehicleMapper
{
public:
	static list<boost::shared_ptr<Abstract_Vehicle>> getAll();

	static void UpdatePosition(const uint32_t Id, const Point & CurrentPosition);

	static void UpdateStatus(const uint32_t Id, const VehicleStatus CurrentStatus, const Point & GoalPosition, const uint64_t EmergencyId, const uint64_t PatientId, const bool IsBlue);

	static VehicleStatus getLastStatus(uint32_t id);
};

class EmergencyMapper
{
public:
	static Point GetEmergencyPoint(uint64_t idEmergency);
};

class TimeTableMapper
{
public:
	static list<TimeEntry> getTimeEntries(int CarId);
};

class HospitalMapper
{
public:
	static list<Hospital> getAll();
};

#endif
