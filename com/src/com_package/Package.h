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

#ifndef PACKAGE_H_
#define PACKAGE_H_

class Package
{
public:
	enum Package_Type
	{
		USER_LOGIN, 
		USER_LOGOUT,
		USER_WALL,
		USER_CHAT,
		USER_MSG,
		USER_LIST,
		CALL_ACCEPT,
		LST_MSG,
		VEHICLE_ALARM,
		VEHICLE_STORNO,
		EMERG_NEW,
		EMERG_UPDATE,
		EMERG_END,
		CASE_NEW,
		CASE_UPDATE,
		CASE_END,
		VEHICLE_MSG,
		VEHICLE_UPDATE,
		VEHICLE_POSITION,
		CALL_ACCEPTED,
		MSG_WALL,
		MSG_CHAT,
		MSG_PRIVATE,
		SERVER_WALL,
		USER_LOGIN_ANSWER,
		USER_LIST_ANSWER,
		QUIT,
	};

	static string Type2String(Package_Type type)
	{
		switch(type)
		{
		case USER_LOGIN:
			return "USER_LOGIN";
		case USER_LOGOUT:
			return "USER_LOGOUT";
		case USER_WALL:
			return "USER_WALL";
		case USER_CHAT:
			return "USER_CHAT";
		case USER_MSG:
			return "USER_MSG";
		case USER_LIST:
			return "USER_LIST";
		case CALL_ACCEPT:
			return "CALL_ACCEPT";
		case LST_MSG:
			return "LST_MSG";
		case VEHICLE_ALARM:
			return "VEHICLE_ALARM";
		case VEHICLE_STORNO:
			return "VEHICLE_STORNO";
		case EMERG_NEW:
			return "EMERG_NEW";
		case EMERG_UPDATE:
			return "EMERG_UPDATE";
		case EMERG_END:
			return "EMERG_END";
		case CASE_NEW:
			return "CASE_NEW";
		case CASE_UPDATE:
			return "CASE_UPDATE";
		case CASE_END:
			return "CASE_END";
		case VEHICLE_MSG:
			return "VEHICLE_MSG";
		case VEHICLE_UPDATE:
			return "VEHICLE_UPDATE";
		case VEHICLE_POSITION:
			return "VEHICLE_POSITION";
		case CALL_ACCEPTED:
			return "CALL_ACCEPTED";
		case MSG_WALL:
			return "MSG_WALL";
		case MSG_CHAT:
			return "MSG_CHAT";
		case MSG_PRIVATE:
			return "MSG_PRIVATE";
		case SERVER_WALL:
			return "SERVER_WALL";
		case USER_LOGIN_ANSWER:
			return "USER_LOGIN_ANSWER";
		case USER_LIST_ANSWER:
			return "USER_LIST_ANSWER";
		case QUIT:
			return "QUIT";
		}
		return "";
	}

	explicit Package(Package_Type type)
		: mType(type)
	{
	}

	Package_Type GetType() const
	{
		return mType;
	}

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType());
	}

	virtual ~Package()
	{

	}

private:
	Package_Type mType;
};

#include "Package_Emergencies.h"
#include "Package_Server.h"
#include "Package_User.h"
#include "Package_Vehicle.h"

#endif
