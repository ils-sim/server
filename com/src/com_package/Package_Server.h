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

#ifndef PACKAGE_SERVER_H_
#define PACKAGE_SERVER_H_

class Message_Wall : public Package
{
public:
	Message_Wall() : Package(Package::MSG_WALL), IdSender(0), NewMessage("") {}
	uint32_t IdSender;
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdSender: " + TToString(IdSender) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class Message_Chat : public Package
{
public:
	Message_Chat() : Package(Package::MSG_CHAT), IdSender(0), NewMessage("") {}
	uint32_t IdSender;
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdSender: " + TToString(IdSender) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class Message_Private : public Package
{
public:
	Message_Private() : Package(Package::MSG_PRIVATE), IdSender(0), NewMessage("") {}
	uint32_t IdSender;
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdSender: " + TToString(IdSender) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class Server_Wall : public Package
{
public:
	Server_Wall() : Package(Package::SERVER_WALL), NewMessage("") {}
	string NewMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"NewMessage: " + TToString(NewMessage);
	}
};

class Quit_ : public Package
{
public:
	Quit_() : Package(Package::QUIT) {}
};

class User_Login_Answer : public Package
{
public:
	User_Login_Answer() : Package(Package::USER_LOGIN_ANSWER), Servertime(0) {}
	uint64_t Servertime;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"Servertime: " + TToString(Servertime);
	}
};

class User_
{
public:
	uint32_t UID;
	uint32_t ControlCenter;
};

class User_List_Answer : public Package
{
public:
	User_List_Answer() : Package(Package::USER_LIST_ANSWER) {}
	vector<User_> UserList;
};

#endif