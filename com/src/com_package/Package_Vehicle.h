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
	enum VehicleStatus
	{
		NOT_USED,
		NOT_OPERATIONAL,
		OPERATIONAL,
		EMERGENCY_ACCEPTED,
		EMERGENCY_ARRIVED,
		EMERGENCY_DEPARTED,
		DESTINATION_ARRIVED,
		DESTINATION_DEPARTED,
		DEPARTMENT_ARRIVED,
		VEHICLE_OCCUPY,
		PATIENT_FOUND,
	};
	
	Vehicle_Update() : Package(Package::VEHICLE_UPDATE), IdVehicle(0), Status(NOT_USED), DestinationLatitude(0.0), DestinationLongitude(0.0), IdEmergency(0), IdPatient(0), BlueLight(false) {}
	uint32_t IdVehicle;
	VehicleStatus Status;
	double DestinationLatitude;
	double DestinationLongitude;
	uint32_t IdEmergency;
	uint32_t IdPatient;
	bool BlueLight;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle) + ", " +
			"Status: " + VehicleStatus2String(Status) + ", " +
			"DestinationLatitude: " + TToString(DestinationLatitude) + ", " +
			"DestinationLongitude: " + TToString(DestinationLongitude) + ", " +
			"IdEmergency: " + TToString(IdEmergency) + ", " +
			"IdPatient: " + TToString(IdPatient) + ", " + 
			"BlueLight: " + TToString(BlueLight);
	}
	
	static string VehicleStatus2String(VehicleStatus status)
	{
		switch(status)
		{
			case NOT_USED:
				return "NOT_USED";
			case NOT_OPERATIONAL:
				return "NOT_OPERATIONAL";
			case OPERATIONAL:
				return "OPERATIONAL";
			case EMERGENCY_ACCEPTED:
				return "EMERGENCY_ACCEPTED";
			case EMERGENCY_ARRIVED:
				return "EMERGENCY_ARRIVED";
			case EMERGENCY_DEPARTED:
				return "EMERGENCY_DEPARTED";
			case DESTINATION_ARRIVED:
				return "DESTINATION_ARRIVED";
			case DESTINATION_DEPARTED:
				return "DESTINATION_DEPARTED";
			case DEPARTMENT_ARRIVED:
				return "DEPARTMENT_ARRIVED";
			case VEHICLE_OCCUPY:
				return "VEHICLE_OCCUPY";
			case PATIENT_FOUND:
				return "PATIENT_FOUND";
		}
		return "";
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
