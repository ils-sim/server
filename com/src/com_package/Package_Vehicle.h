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

#ifndef PACKAGE_VEHICLE_H_
#define PACKAGE_VEHICLE_H_

class Vehicle_Alarm : public Package
{
public:
	Vehicle_Alarm() : Package(Package::VEHICLE_ALARM), IdVehicle(0), IdEmergency(0), BlueLight(false) {}
	uint32_t IdVehicle;
	uint64_t IdEmergency;
	bool BlueLight;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle) + ", " +
			"IdEmergency: " + TToString(IdEmergency) + ", " +
			"BlueLight: " + TToString(BlueLight);
	}
};

class Vehicle_Storno : public Package
{
public:
	Vehicle_Storno() : Package(Package::VEHICLE_STORNO), IdVehicle(0), IdEmergency(0) {}
	uint32_t IdVehicle;
	uint64_t IdEmergency;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle) + ", " +
			"IdEmergency: " + TToString(IdEmergency);
	}
};

class Vehicle_Message : public Package
{
public:
	Vehicle_Message() : Package(Package::VEHICLE_MSG), IdVehicle(0), NewMessage("") {}
	uint32_t IdVehicle;
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class Vehicle_Update : public Package
{
public:
	Vehicle_Update() : Package(Package::VEHICLE_UPDATE), IdVehicle(0) {}
	uint32_t IdVehicle;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle);
	}
};

class Vehicle_Position : public Package
{
public:
	Vehicle_Position() : Package(Package::VEHICLE_POSITION), IdVehicle(0), Latitude(0.0), Longitude(0.0) {}
	uint32_t IdVehicle;
	double Latitude;
	double Longitude;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle) + ", " +
			"Latitude: " + TToString(Latitude) + ", " +
			"Longitude: " + TToString(Longitude);
	}
};

#endif