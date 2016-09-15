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
#include <list>

using namespace std;

#include "com_convert/convert.h"
#include "com_log/Log.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "com_sql_client/SQL_Client.h"

#include "Position.h"
#include "Vehicle_Status.h"
#include "TimeTable.h"
#include "Route.h"
#include "Abstract_Vehicle.h"
#include "Vehicle_Amb.h"
#include "Hospital.h"

#include "Database.h"

list<boost::shared_ptr<Abstract_Vehicle>> VehicleMapper::getAll()
{
	list<boost::shared_ptr<Abstract_Vehicle>> CarList;
	Log::GetInstance()->WriteDebug("Starting Downloading Cars from MySQL-Server");
	boost::shared_ptr<SQL_Client> client = Generate_SQL_Client("new_ilssim");
	string str = "SELECT idFahrzeuge, Rufname, Wachen_idWachen, FahrzeugTyp_idFahrzeugTyp, Latitude, Longitude FROM `Fahrzeuge`, `Wachen`";
	str += " WHERE idWachen = Wachen_idWachen";
	str += " AND (Wachen_idWachen = 4 OR Wachen_idWachen = 5 OR Wachen_idWachen = 6 OR Wachen_idWachen = 1212 OR Wachen_idWachen = 1213);";
	boost::shared_ptr<SQL_Result> sql_result = client->SendQueryReturn(str);
	while(sql_result->next())
	{
		double Lat = sql_result->getDouble(4);
		double Long = sql_result->getDouble(5);
		Point point = Point(Long, Lat);
		if(point.isZerro())
		{
			Log::GetInstance()->WriteWarning("Car has no valid Station: " + sql_result->getString(0));
			continue;
		}
		boost::shared_ptr<Abstract_Vehicle> newCar;
		int type_ = sql_result->getInt(3);
		switch (type_)
		{
		case 1:   // NEF
		case 2:   // RTW
		case 9:   // ITW
		case 206: // SEW
		case 3:   // KTW
		case 207: // B-KTW
			{
				Log::GetInstance()->WriteWarning("Generating NEF, RTW, ITW, SEW, KTW, B-KTW: " + sql_result->getString(1));
				boost::shared_ptr<Abstract_Vehicle> Car(new Vehicle_Ambulance(sql_result->getInt(0), sql_result->getString(1), point));
				CarList.push_back(Car);
			}
			break;
		default:
			Log::GetInstance()->WriteError("No Class defined for Type: " + TToString(type_));
			break;
		}
	}
	return CarList;
}

void VehicleMapper::UpdatePosition(const uint32_t Id, const Point & CurrentPosition)
{
	Log::GetInstance()->WriteDebug("Updating Car Position (" + TToString(Id) + ").");
	string str = "INSERT INTO  `FahrzeugPosition` (`idFahrzeug`, `AktuelleZeit`, `PosLat`, `PosLong`)";
	str += "VALUES ('" + TToString(Id) + "', '" + Time_ttoMySQLTime(boost::posix_time::microsec_clock::universal_time()) + "', '" + DoubleToString(CurrentPosition.GetLat()) + "',  '" + DoubleToString(CurrentPosition.GetLong()) + "');";
	SQL_ClientGlobal::GetInstance()->AddNewInsertCommand(str, "online_ilssim");

	//MySQL_Client Client("new_ilssim");
	//Client.SendQueryNoReturn(str);
}

void VehicleMapper::UpdateStatus(const uint32_t Id, const VehicleStatus CurrentStatus, const Point & GoalPosition, const uint64_t EmergencyId, const uint64_t PatientId, const bool IsBlue)
{
	Log::GetInstance()->WriteDebug("Updating Car Status (" + TToString(Id) + ").");
	string EinsatzId = "NULL";
	if(EmergencyId != 0)
	{
		EinsatzId = TToString(EmergencyId);
	}
	string lPatientId = "NULL";
	if(PatientId != 0)
	{
		lPatientId = TToString(PatientId);
	}
	string str = "INSERT INTO `FahrzeugUpdate` (`idFahrzeug`, `AktuelleZeit`, `FahrzeugStatus_idFahrzeugStatus`, `ZielPosLat`, `ZielPosLong`, `Einsatz_idEinsatz`, `Patient_idPatient`, `Einsatz_Blau`, `IsServerStatus`, `UsersOnline_idUsersOnline`)";
	str += "VALUES ('" + TToString(Id) + "', '" + Time_ttoMySQLTime(boost::posix_time::microsec_clock::universal_time()) + "', '" + TToString((int)CurrentStatus) + "', '" + DoubleToString(GoalPosition.GetLat()) + "', '" + DoubleToString(GoalPosition.GetLong()) + "', " + TToString(EinsatzId) + ", " + TToString(lPatientId) + ", " + TToString((int)IsBlue) + ", '1', NULL);";
	SQL_ClientGlobal::GetInstance()->AddNewInsertCommand(str, "online_ilssim");

	//boost::shared_ptr<SQL_Client> client = Generate_SQL_Client("new_ilssim");
	//client->SendQueryNoReturn(str);
}

VehicleStatus VehicleMapper::getLastStatus(uint32_t id)
{
	boost::shared_ptr<SQL_Client> client = Generate_SQL_Client("online_ilssim");
	string str = "SELECT FahrzeugStatus_idFahrzeugStatus FROM `FahrzeugUpdate` WHERE idFahrzeug = '" + TToString(id) + "' ORDER BY AktuelleZeit DESC LIMIT 1;";
	boost::shared_ptr<SQL_Result> sql_result = client->SendQueryReturn(str);
	while(sql_result->next())
	{
		return (VehicleStatus)sql_result->getInt(0);
	}
	return EintreffenDienststelle;
}


//cppcheck-suppress unusedFunction
Point EmergencyMapper::GetEmergencyPoint(uint64_t idEmergency)
{
	boost::shared_ptr<SQL_Client> client = Generate_SQL_Client("online_ilssim");
	string str = "SELECT `PosLat`, `PosLong` FROM `Einsatz` WHERE `idEinsatz` = '" + TToString(idEmergency) + "';";
	boost::shared_ptr<SQL_Result> sql_result = client->SendQueryReturn(str);
	while(sql_result->next())
	{
		double Lat = sql_result->getDouble(0);
		double Long = sql_result->getDouble(1);
		return Point(Long, Lat);
	}
	return Point(0.0, 0.0);
}


list<TimeEntry> TimeTableMapper::getTimeEntries(int CarId)
{
	list<TimeEntry> mTable;
	Log::GetInstance()->WriteDebug("Get time tables of Car (" + TToString(CarId) + ").");
	boost::shared_ptr<SQL_Client> client = Generate_SQL_Client("new_ilssim");
	string str = "SELECT VonZeit, BisZeit, Montag, Dienstag, Mittwoch, Donnerstag, Freitag, Samstag, Sonntag FROM `Dienstzeiten` WHERE `Fahrzeuge_idFahrzeuge` = ";
	str += TToString(CarId);
	boost::shared_ptr<SQL_Result> sql_result = client->SendQueryReturn(str);
	while(sql_result->next())
	{
		if(sql_result->getInt(2))
		{
			// Montag
			mTable.push_back(TimeEntry(BASE_MO, sql_result->getString(0), sql_result->getString(1)));
		}
		if(sql_result->getInt(3))
		{
			// Dienstag
			mTable.push_back(TimeEntry(BASE_DI, sql_result->getString(0), sql_result->getString(1)));
		}
		if(sql_result->getInt(4))
		{
			// Mittwoch
			mTable.push_back(TimeEntry(BASE_MI, sql_result->getString(0), sql_result->getString(1)));
		}
		if(sql_result->getInt(5))
		{
			// Donnerstag
			mTable.push_back(TimeEntry(BASE_DO, sql_result->getString(0), sql_result->getString(1)));
		}
		if(sql_result->getInt(6))
		{
			// Freitag
			mTable.push_back(TimeEntry(BASE_FR, sql_result->getString(0), sql_result->getString(1)));
		}
		if(sql_result->getInt(7))
		{
			// Samstag
			mTable.push_back(TimeEntry(BASE_SA, sql_result->getString(0), sql_result->getString(1)));
		}
		if(sql_result->getInt(8))
		{
			// Sonntag
			mTable.push_back(TimeEntry(BASE_SO, sql_result->getString(0), sql_result->getString(1)));
		}
	}
	return mTable;
}

list<Hospital> HospitalMapper::getAll()
{
	boost::shared_ptr<SQL_Client> client = Generate_SQL_Client("new_ilssim");
	string str = "SELECT `idKrankenhaus`, `Name`, `Latitude`, `Longitude` FROM `Krankenhaus`;";
	boost::shared_ptr<SQL_Result> sql_result = client->SendQueryReturn(str);
	list<Hospital> list;
	while(sql_result->next())
	{
		Point p(sql_result->getDouble(3), sql_result->getDouble(2));
		list.push_back(Hospital(sql_result->getInt(0), sql_result->getString(1), p));
	}
	return list;
}
