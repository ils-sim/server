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

#ifndef FROM_CLIENT_CMDS_H_
#define FROM_CLIENT_CMDS_H_

class UserLogin_Cmd : public CLI_Command
{
public:
	UserLogin_Cmd()
		: CLI_Command("UserLogin", "User loggt sich ein.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_Login> p(new User_Login);
        p->UID = GetInt("UID", stream);
        p->ControlCenter = GetInt("ControlCenter", stream);
        p->Password = GetString("Password", stream);
		pClient->Send(p);
	}
};

class UserLogout_Cmd : public CLI_Command
{
public:
	UserLogout_Cmd()
		: CLI_Command("UserLogout", "User loggt sich aus.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_Logout> p(new User_Logout);
		p->UID = GetInt("UID", stream);
		pClient->Send(p);
	}
};

class UserWall_Cmd : public CLI_Command
{
public:
	UserWall_Cmd()
		: CLI_Command("UserWall", "Nachricht an alle Benutzer.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_Wall> p(new User_Wall);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class UserChat_Cmd : public CLI_Command
{
public:
	UserChat_Cmd()
		: CLI_Command("UserChat", "Nachricht an alle Benutzer innerhalb einer LSt.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_Chat> p(new User_Chat);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class UserMsg_Cmd : public CLI_Command
{
public:
	UserMsg_Cmd()
		: CLI_Command("UserMsg", "Nachricht an einen Benutzer.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_Msg> p(new User_Msg);
		p->UIDReciever = GetInt("UIDReciever", stream);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class UserList_Cmd : public CLI_Command
{
public:
	UserList_Cmd()
		: CLI_Command("UserList", "Liste aller eingeloggten Benutzer.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_List> p(new User_List);
		pClient->Send(p);
	}
};

class CallAccept_Cmd : public CLI_Command
{
public:
	CallAccept_Cmd()
		: CLI_Command("CallAccept", "Nimmt eingehenden Anruf an.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Call_Accept> p(new Call_Accept);
		p->IdEmergency = GetInt("IdEmergency", stream);
		pClient->Send(p);
	}
};

class LstMsg_Cmd : public CLI_Command
{
public:
	LstMsg_Cmd()
		: CLI_Command("LstMsg", "Nachricht an ein Fahrzeug.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Lst_Msg> p(new Lst_Msg);
		p->IdVehicle = GetInt("IdVehicle", stream);
		p->IdMessage = GetInt("IdMessage", stream);
		pClient->Send(p);
	}
};

class VehicleAlarm_Cmd : public CLI_Command
{
public:
	VehicleAlarm_Cmd()
		: CLI_Command("VehicleAlarm", "Fahrzeug zu Einsatz zuweisen.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Vehicle_Alarm> p(new Vehicle_Alarm);
		p->IdVehicle = GetInt("IdVehicle", stream);
		p->IdEmergency = GetInt("IdEmergency", stream);
		p->BlueLight = GetBool("BlueLight", stream);
		pClient->Send(p);
	}
};

class VehicleStorno_Cmd : public CLI_Command
{
public:
	VehicleStorno_Cmd()
		: CLI_Command("VehicleStorno", "Fahrzeug storniert.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Vehicle_Storno> p(new Vehicle_Storno);
		p->IdVehicle = GetInt("IdVehicle", stream);
		p->IdEmergency = GetInt("IdEmergency", stream);
		pClient->Send(p);
	}
};

#endif