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

#ifndef PACKAGE_USER_H_
#define PACKAGE_USER_H_

class User_Login : public Package
{
public:
	User_Login() : Package(Package::USER_LOGIN), UID(0), ControlCenter(0), Password("") {}
	uint32_t UID;
	uint32_t ControlCenter;
	string Password;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"UID: " + TToString(UID) + ", " +
			"ControlCenter: " + TToString(ControlCenter) + //", " + 
			//"Password: " + TToString(Password) +
			"\n";
	}
};

class User_Logout : public Package
{
public:
	User_Logout() : Package(Package::USER_LOGOUT), UID(0) {}
	uint32_t UID;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"UID: " + TToString(UID);
	}
};

class User_Wall : public Package
{
public:
	User_Wall() : Package(Package::USER_WALL), NewMessage("") {}
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class User_Chat : public Package
{
public:
	User_Chat() : Package(Package::USER_CHAT), NewMessage("") {}
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class User_Msg : public Package
{
public:
	User_Msg() : Package(Package::USER_MSG), UIDReciever(0), NewMessage("") {}
	uint32_t UIDReciever;
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"UIDReciever: " + TToString(UIDReciever) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class User_List : public Package
{
public:
	User_List() : Package(Package::USER_LIST) {}

};

#endif