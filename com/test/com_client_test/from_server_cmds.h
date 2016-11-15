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

#ifndef FROM_SERVER_CMDS_H_
#define FROM_SERVER_CMDS_H_

class EmergNew_Cmd : public CLI_Command
{
public:
	EmergNew_Cmd()
		: CLI_Command("EmergNew", "Neuer Noteinsatz.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Emergency_New> p(new Emergency_New);
		p->IdEmergency = GetInt("IdEmergency", stream);
		pClient->Send(p);
	}
};

class EmergUpdate_Cmd : public CLI_Command
{
public:
	EmergUpdate_Cmd()
		: CLI_Command("EmergUpdate", "Aktualisierung von Einsatz - Stream schauen.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Emergency_Update> p(new Emergency_Update);
		p->IdEmergency = GetInt("IdEmergency", stream);
		pClient->Send(p);
	}
};

class EmergEnd_Cmd : public CLI_Command
{
public:
	EmergEnd_Cmd()
		: CLI_Command("EmergEnd", "Ende des Noteinsatzes.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Emergency_End> p(new Emergency_End);
		p->IdEmergency = GetInt("IdEmergency", stream);
		pClient->Send(p);
	}
};

class CaseNew_Cmd : public CLI_Command
{
public:
	CaseNew_Cmd()
		: CLI_Command("CaseNew", "Neuer KT-Einsatz.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Case_New> p(new Case_New);
		p->IdCase = GetInt("IdCase", stream);
		pClient->Send(p);
	}
};

class CaseUpdate_Cmd : public CLI_Command
{
public:
	CaseUpdate_Cmd()
		: CLI_Command("CaseUpdate", "Aktualisierung von KT - Stream schauen.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Case_Update> p(new Case_Update);
		p->IdCase = GetInt("IdCase", stream);
		pClient->Send(p);
	}
};

class CaseEnd_Cmd : public CLI_Command
{
public:
	CaseEnd_Cmd()
		: CLI_Command("CaseEnd", "Ende des KT-Einsatzes.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Case_End> p(new Case_End);
		p->IdCase = GetInt("IdCase", stream);
		pClient->Send(p);
	}
};

class VehicleMsg_Cmd : public CLI_Command
{
public:
	VehicleMsg_Cmd()
		: CLI_Command("VehicleMsg", "Nachricht von Fahrzeug an Leitstelle.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Vehicle_Message> p(new Vehicle_Message);
		p->IdVehicle = GetInt("IdVehicle", stream);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class VehicleUpdate_Cmd : public CLI_Command
{
public:
	VehicleUpdate_Cmd()
		: CLI_Command("VehicleUpdate", "Aktualisierung von Status des Fahrzeug - Stream schauen.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Vehicle_Update> p(new Vehicle_Update);
		p->IdVehicle = GetInt("IdVehicle", stream);
		p->Status = (Vehicle_Update::VehicleStatus)GetInt("Status", stream);
		p->DestinationLatitude = GetDouble("DestinationLatitude", stream);
		p->DestinationLongitude = GetDouble("DestinationLongitude", stream);
		p->IdEmergency = GetInt("IdEmergency", stream);
		p->IdPatient = GetInt("IdPatient", stream);
		p->BlueLight = GetBool("BlueLight", stream);
		pClient->Send(p);
	}
};

class VehiclePosition_Cmd : public CLI_Command
{
public:
	VehiclePosition_Cmd()
		: CLI_Command("VehiclePosition", "Aktualisieren der Fahrzeugposition.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Vehicle_Position> p(new Vehicle_Position);
		p->IdVehicle = GetInt("IdVehicle", stream);
		p->Latitude = GetDouble("Latitude", stream);
		p->Longitude = GetDouble("Longitude", stream);
		pClient->Send(p);
	}
};

class CallAccepted_Cmd : public CLI_Command
{
public:
	CallAccepted_Cmd()
		: CLI_Command("CallAccepted", "Ein Anruf wurde von einem Disponenten angenommen.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Call_Accepted> p(new Call_Accepted);
		p->IdReciever = GetInt("IdReciever", stream);
		p->IdEmergency = GetInt("IdEmergency", stream);
		pClient->Send(p);
	}
};

class MsgWall_Cmd : public CLI_Command
{
public:
	MsgWall_Cmd()
		: CLI_Command("MsgWall", "Eine Broadcast-Nachricht.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Message_Wall> p(new Message_Wall);
		p->IdSender = GetInt("IdSender", stream);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class MsgChat_Cmd : public CLI_Command
{
public:
	MsgChat_Cmd()
		: CLI_Command("MsgChat", "Eine interne Nachricht auf Lst Level.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Message_Chat> p(new Message_Chat);
		p->IdSender = GetInt("IdSender", stream);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class MsgPrivate_Cmd : public CLI_Command
{
public:
	MsgPrivate_Cmd()
		: CLI_Command("MsgPrivate", "Eine private Chat-Nachricht.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Message_Private> p(new Message_Private);
		p->IdSender = GetInt("IdSender", stream);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class ServerWall_Cmd : public CLI_Command
{
public:
	ServerWall_Cmd()
		: CLI_Command("ServerWall", "Nachricht an alle Benutzer vom Server.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Server_Wall> p(new Server_Wall);
		p->NewMessage = GetString("NewMessage", stream);
		pClient->Send(p);
	}
};

class UserLoginAnswer_Cmd : public CLI_Command
{
public:
	UserLoginAnswer_Cmd()
		: CLI_Command("UserLoginAnswer", "Gibt zurück, ob Loginvorgang erfolgreich war.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_Login_Answer> p(new User_Login_Answer);
		p->Servertime = GetInt("Servertime", stream);
		pClient->Send(p);
	}
};

class UserListAnswer_Cmd : public CLI_Command
{
public:
	UserListAnswer_Cmd()
		: CLI_Command("UserListAnswer", "Gibt zurück, welche User gerade angemeldet sind.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<User_List_Answer> p(new User_List_Answer);
		pClient->Send(p);
	}
};

class Quit_Cmd : public CLI_Command
{
public:
	Quit_Cmd()
		: CLI_Command("Quit", "Server beendet seine Dienste.")
	{}

	virtual void Run(std::istream & stream)
	{       
		boost::shared_ptr<Quit_> p(new Quit_);
		pClient->Send(p);
	}
};

#endif
