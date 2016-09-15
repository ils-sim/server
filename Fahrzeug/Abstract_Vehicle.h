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

#ifndef CAR_H_
#define CAR_H_

class Abstract_Vehicle : public Task
{
public:

	Abstract_Vehicle(uint32_t Id, string Callsign, Point StationPosition, VehicleType type);

	void AddToEmergency(uint64_t emergency, bool isBlue, Point position);
	void RemoveFromEmergency();

	int GetId() const;
	string GetCallsign() const;
	Point GetCurrentPosition() const;
	VehicleType GetType() const;
	VehicleStatus GetStatus() const;

	void PrintCar() const;

	void UpdatePosition();
	void UpdateStatus();

	virtual void run();

	virtual void isStatusNichtEinsatzbereit() = 0;
	virtual void isStatusEinsatzbereit() = 0;
	virtual void isStatusEinsatzAkzeptiert() = 0;
	virtual void isStatusAnkunftEinsatzort() = 0;
	virtual void isStatusAbfahrtEinsatzort() = 0;
	virtual void isStatusAnkunftZielort() = 0;
	virtual void isStatusAbfahrtZielort() = 0;
	virtual void isStatusEintreffenDienststelle() = 0;
	virtual void isStatusFahrzeugBesetzen() = 0;
	virtual void isStatusPatientGefunden() = 0;

protected:
	const uint32_t mId;
	const string mCallsign;
	const Point mStationPoint;
	const VehicleType mCarType;
	TimeTable mTimeTables;

	VehicleStatus mCurrentStatus;
	Point mCurrentPosition;
	shared_ptr<Route> mRoute;

	uint64_t mEmergencyId;
	bool mIsBlue;
	uint64_t mPatientId;
	Point mGoalPosition;
};

#define KM_H2M_S(value) (value / 3.6)

#endif
