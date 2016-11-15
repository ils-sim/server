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

#include <string>
#include <stdint.h>
#include <vector>

using namespace std;

#include <boost/shared_ptr.hpp>

#include "protocol.pb.h"
#include "com_convert/convert.h"
#include "Package.h"
#include "Package_Converter.h"


boost::shared_ptr<Package> Package_Converter::Protocol2Package(Protocol protocol)
{
	boost::shared_ptr<Package> pPackage;
	switch(protocol.type())
	{
	case Protocol_Type_USER_LOGIN:		// user.proto
		{
			UserLogin user_login = protocol.user_login();
			pPackage.reset(new User_Login);
			boost::shared_ptr<User_Login> obj_ = boost::dynamic_pointer_cast<User_Login>(pPackage);
			obj_->UID = user_login.uid();
			obj_->ControlCenter = user_login.control_center();
			obj_->Password = user_login.password();
		}
		break;
	case Protocol_Type_USER_LOGOUT:
		{
			UserLogout user_logout = protocol.user_logout();
			pPackage.reset(new User_Logout);
			boost::shared_ptr<User_Logout> obj_ = boost::dynamic_pointer_cast<User_Logout>(pPackage);
			obj_->UID = user_logout.uid();
		}
		break;
	case Protocol_Type_USER_WALL:
		{
			UserWall user_wall = protocol.user_wall();
			pPackage.reset(new User_Wall);
			boost::shared_ptr<User_Wall> obj_ = boost::dynamic_pointer_cast<User_Wall>(pPackage);
			obj_->NewMessage = user_wall.new_message();
		}
		break;
	case Protocol_Type_USER_CHAT:
		{
			UserChat user_chat = protocol.user_chat();
			pPackage.reset(new User_Chat);
			boost::shared_ptr<User_Chat> obj_ = boost::dynamic_pointer_cast<User_Chat>(pPackage);
			obj_->NewMessage = user_chat.new_message();
		}
		break;
	case Protocol_Type_USER_MSG:
		{
			UserMsg user_msg = protocol.user_msg(); 
			pPackage.reset(new User_Msg);
			boost::shared_ptr<User_Msg> obj_ = boost::dynamic_pointer_cast<User_Msg>(pPackage);
			obj_->UIDReciever = user_msg.uid_reciever();
			obj_->NewMessage = user_msg.new_message();
		}
		break;
	case Protocol_Type_USER_LIST:
		{
			UserList user_list = protocol.user_list();
			pPackage.reset(new User_List);
			boost::shared_ptr<User_List> obj_ = boost::dynamic_pointer_cast<User_List>(pPackage);
			// do the stuff...
		}
		break;
	case Protocol_Type_CALL_ACCEPT:		// emergencies.proto
		{
			CallAccept call_accept = protocol.call_accept();
			pPackage.reset(new Call_Accept);
			boost::shared_ptr<Call_Accept> obj_ = boost::dynamic_pointer_cast<Call_Accept>(pPackage);
			obj_->IdEmergency = call_accept.id_emerg();
		}
		break;
	case Protocol_Type_EMERG_NEW:
		{
			EmergNew emerg = protocol.emerg_new();
			pPackage.reset(new Emergency_New);
			boost::shared_ptr<Emergency_New> obj_ = boost::dynamic_pointer_cast<Emergency_New>(pPackage);
			obj_->IdEmergency = emerg.id_emerg();
		}
		break;
	case Protocol_Type_EMERG_UPDATE:
		{
			EmergUpdate emerg = protocol.emerg_update();
			pPackage.reset(new Emergency_Update);
			boost::shared_ptr<Emergency_Update> obj_ = boost::dynamic_pointer_cast<Emergency_Update>(pPackage);
			obj_->IdEmergency = emerg.id_emerg();
		}
		break;
	case Protocol_Type_EMERG_END:
		{
			EmergEnd emerg = protocol.emerg_end();
			pPackage.reset(new Emergency_End);
			boost::shared_ptr<Emergency_End> obj_ = boost::dynamic_pointer_cast<Emergency_End>(pPackage);
			obj_->IdEmergency = emerg.id_emerg();
		}
		break;
	case Protocol_Type_CASE_NEW:
		{
			CaseNew case_new = protocol.case_new();
			pPackage.reset(new Case_New);
			boost::shared_ptr<Case_New> obj_ = boost::dynamic_pointer_cast<Case_New>(pPackage);
			obj_->IdCase = case_new.id_case();
		}
		break;
	case Protocol_Type_CASE_UPDATE:
		{
			CaseUpdate case_update = protocol.case_update();
			pPackage.reset(new Case_Update);
			boost::shared_ptr<Case_Update> obj_ = boost::dynamic_pointer_cast<Case_Update>(pPackage);
			obj_->IdCase = case_update.id_case();
		}
		break;
	case Protocol_Type_CASE_END:
		{
			CaseEnd case_end = protocol.case_end();
			pPackage.reset(new Case_End);
			boost::shared_ptr<Case_End> obj_ = boost::dynamic_pointer_cast<Case_End>(pPackage);
			obj_->IdCase = case_end.id_case();
		}
		break;
	case Protocol_Type_CALL_ACCEPTED:
		{
			CallAccepted call = protocol.call_accepted();
			pPackage.reset(new Call_Accepted);
			boost::shared_ptr<Call_Accepted> obj_ = boost::dynamic_pointer_cast<Call_Accepted>(pPackage);
			obj_->IdEmergency = call.id_emerg();
			obj_->IdReciever = call.id_reciever();
		}
		break;
	case Protocol_Type_LST_MSG:
		{
			LstMsg lst_msg = protocol.lst_msg();
			pPackage.reset(new Lst_Msg);
			boost::shared_ptr<Lst_Msg> obj_ = boost::dynamic_pointer_cast<Lst_Msg>(pPackage);
			obj_->IdVehicle = lst_msg.id_vehicle();
			obj_->IdMessage = lst_msg.id_message();
		}
		break;
	case Protocol_Type_VEHICLE_ALARM:		// vehicle.proto
		{
			VehicleAlarm alarm = protocol.vehicle_alarm();
			pPackage.reset(new Vehicle_Alarm);
			boost::shared_ptr<Vehicle_Alarm> obj_ = boost::dynamic_pointer_cast<Vehicle_Alarm>(pPackage);
			obj_->IdVehicle = alarm.id_vehicle();
			obj_->IdEmergency = alarm.id_emerg();
			obj_->BlueLight = alarm.blue_light();
		}
		break;
	case Protocol_Type_VEHICLE_STORNO:
		{
			VehicleStorno storno = protocol.vehicle_stornno();
			pPackage.reset(new Vehicle_Storno);
			boost::shared_ptr<Vehicle_Storno> obj_ = boost::dynamic_pointer_cast<Vehicle_Storno>(pPackage);
			obj_->IdVehicle = storno.id_vehicle();
			obj_->IdEmergency = storno.id_emerg();
		}
		break;
	case Protocol_Type_VEHICLE_MSG:
		{
			VehicleMsg msg = protocol.vehicle_msg();
			pPackage.reset(new Vehicle_Message);
			boost::shared_ptr<Vehicle_Message> obj_ = boost::dynamic_pointer_cast<Vehicle_Message>(pPackage);
			obj_->IdVehicle = msg.id_vehicle();
			obj_->NewMessage = msg.new_message();
		}
		break;
	case Protocol_Type_VEHICLE_UPDATE:
		{
			VehicleUpdate update = protocol.vehicle_update();
			pPackage.reset(new Vehicle_Update);
			boost::shared_ptr<Vehicle_Update> obj_ = boost::dynamic_pointer_cast<Vehicle_Update>(pPackage);
			obj_->IdVehicle = update.id_vehicle();
			obj_->Status = (Vehicle_Update::VehicleStatus)update.status();
			obj_->DestinationLatitude = update.destination_latitude();
			obj_->DestinationLongitude = update.destination_longitude();
			obj_->IdEmergency = update.id_emerg();
			obj_->IdPatient = update.id_patient();
			obj_->BlueLight = update.blue_light();
		}
		break;
	case Protocol_Type_VEHICLE_POSITION:
		{
			VehiclePosition pos = protocol.vehicle_position();
			pPackage.reset(new Vehicle_Position);
			boost::shared_ptr<Vehicle_Position> obj_ = boost::dynamic_pointer_cast<Vehicle_Position>(pPackage);
			obj_->IdVehicle = pos.id_vehicle();
			obj_->Latitude = pos.latitude();
			obj_->Longitude = pos.longitude();
		}
		break;
	case Protocol_Type_MSG_WALL:		// server.proto
		{
			MsgWall wall = protocol.msg_wall();
			pPackage.reset(new Message_Wall);
			boost::shared_ptr<Message_Wall> obj_ = boost::dynamic_pointer_cast<Message_Wall>(pPackage);
			obj_->IdSender = wall.id_sender();
			obj_->NewMessage = wall.new_message();
		}
		break;
	case Protocol_Type_MSG_CHAT:
		{
			MsgChat chat = protocol.msg_chat();
			pPackage.reset(new Message_Chat);
			boost::shared_ptr<Message_Chat> obj_ = boost::dynamic_pointer_cast<Message_Chat>(pPackage);
			obj_->IdSender = chat.id_sender();
			obj_->NewMessage = chat.new_message();
		}
		break;
	case Protocol_Type_MSG_PRIVATE:
		{
			MsgPrivate chat = protocol.msg_private();
			pPackage.reset(new Message_Private);
			boost::shared_ptr<Message_Private> obj_ = boost::dynamic_pointer_cast<Message_Private>(pPackage);
			obj_->IdSender = chat.id_sender();
			obj_->NewMessage = chat.new_message();
		}
		break;
	case Protocol_Type_SERVER_WALL:
		{
			ServerWall wall = protocol.server_wall();
			pPackage.reset(new Server_Wall);
			boost::shared_ptr<Server_Wall> obj_ = boost::dynamic_pointer_cast<Server_Wall>(pPackage);
			obj_->NewMessage = wall.new_message();
		}
		break;
	case Protocol_Type_QUIT:
		{
			Quit quit = protocol.quit();
			pPackage.reset(new Quit_);
		}
		break;
	case Protocol_Type_USER_LOGIN_ANSWER:
		{
			UserLoginAnswer answer = protocol.user_login_answer();
			pPackage.reset(new User_Login_Answer);
			boost::shared_ptr<User_Login_Answer> obj_ = boost::dynamic_pointer_cast<User_Login_Answer>(pPackage);
			obj_->Servertime = answer.servertime();
		}
		break;
	case Protocol_Type_USER_LIST_ANSWER:
		{
			UserListAnswer answer = protocol.user_list_answer();
			pPackage.reset(new User_List_Answer);
			boost::shared_ptr<User_List_Answer> obj_ = boost::dynamic_pointer_cast<User_List_Answer>(pPackage);
			// todo
		}
		break;
	default:
		break;
	}
	return pPackage;
}

Protocol Package_Converter::Package2Protocol(boost::shared_ptr<Package> pPackage)
{
	Protocol protocol;

	switch (pPackage->GetType())
	{
	case Package::USER_LOGIN:		// user.proto
		{
			protocol.set_type(Protocol_Type_USER_LOGIN);
			UserLogin * obj = protocol.mutable_user_login();
			boost::shared_ptr<User_Login> obj_ = boost::dynamic_pointer_cast<User_Login>(pPackage);
			obj->set_uid(obj_->UID);
			obj->set_control_center(obj_->ControlCenter);
			obj->set_password(obj_->Password);
		}
		break;
	case Package::USER_LOGOUT:
		{
			protocol.set_type(Protocol_Type_USER_LOGOUT);
			UserLogout * obj = protocol.mutable_user_logout();
			boost::shared_ptr<User_Logout> obj_ = boost::dynamic_pointer_cast<User_Logout>(pPackage);
			obj->set_uid(obj_->UID);
		}
		break;
	case Package::USER_WALL:
		{
			protocol.set_type(Protocol_Type_USER_WALL);
			UserWall * obj = protocol.mutable_user_wall();
			boost::shared_ptr<User_Wall> obj_ = boost::dynamic_pointer_cast<User_Wall>(pPackage);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::USER_CHAT:
		{
			protocol.set_type(Protocol_Type_USER_CHAT);
			UserChat * obj = protocol.mutable_user_chat();
			boost::shared_ptr<User_Chat> obj_ = boost::dynamic_pointer_cast<User_Chat>(pPackage);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::USER_MSG:
		{
			protocol.set_type(Protocol_Type_USER_MSG);
			UserMsg * obj = protocol.mutable_user_msg();
			boost::shared_ptr<User_Msg> obj_ = boost::dynamic_pointer_cast<User_Msg>(pPackage);
			obj->set_uid_reciever(obj_->UIDReciever);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::USER_LIST:
		{
			protocol.set_type(Protocol_Type_USER_LIST);
			UserList * obj = protocol.mutable_user_list();
			boost::shared_ptr<User_List> obj_ = boost::dynamic_pointer_cast<User_List>(pPackage);
			// todo
			UNUSED(obj);
		}
		break;
	case Package::CALL_ACCEPT:		// emergencies.proto
		{
			protocol.set_type(Protocol_Type_CALL_ACCEPT);
			CallAccept * obj = protocol.mutable_call_accept();
			boost::shared_ptr<Call_Accept> obj_ = boost::dynamic_pointer_cast<Call_Accept>(pPackage);
			obj->set_id_emerg(obj_->IdEmergency);
		}
		break;
	case Package::EMERG_NEW:
		{
			protocol.set_type(Protocol_Type_EMERG_NEW);
			EmergNew * obj = protocol.mutable_emerg_new();
			boost::shared_ptr<Emergency_New> obj_ = boost::dynamic_pointer_cast<Emergency_New>(pPackage);
			obj->set_id_emerg(obj_->IdEmergency);
			UNUSED(obj);
		}
		break;
	case Package::EMERG_UPDATE:
		{
			protocol.set_type(Protocol_Type_EMERG_UPDATE);
			EmergUpdate * obj = protocol.mutable_emerg_update();
			boost::shared_ptr<Emergency_Update> obj_ = boost::dynamic_pointer_cast<Emergency_Update>(pPackage);
			obj->set_id_emerg(obj_->IdEmergency);
		}
		break;
	case Package::EMERG_END:
		{
			protocol.set_type(Protocol_Type_EMERG_END);
			EmergEnd * obj = protocol.mutable_emerg_end();
			boost::shared_ptr<Emergency_End> obj_ = boost::dynamic_pointer_cast<Emergency_End>(pPackage);
			obj->set_id_emerg(obj_->IdEmergency);
		}
		break;
	case Package::CASE_NEW:
		{
			protocol.set_type(Protocol_Type_CASE_NEW);
			CaseNew * obj = protocol.mutable_case_new();
			boost::shared_ptr<Case_New> obj_ = boost::dynamic_pointer_cast<Case_New>(pPackage);
			obj->set_id_case(obj_->IdCase);
		}
		break;
	case Package::CASE_UPDATE:
		{
			protocol.set_type(Protocol_Type_CASE_UPDATE);
			CaseUpdate * obj = protocol.mutable_case_update();
			boost::shared_ptr<Case_Update> obj_ = boost::dynamic_pointer_cast<Case_Update>(pPackage);
			obj->set_id_case(obj_->IdCase);
		}
		break;
	case Package::CASE_END:
		{
			protocol.set_type(Protocol_Type_CASE_END);
			CaseEnd * obj = protocol.mutable_case_end();
			boost::shared_ptr<Case_End> obj_ = boost::dynamic_pointer_cast<Case_End>(pPackage);
			obj->set_id_case(obj_->IdCase);
		}
		break;
	case Package::CALL_ACCEPTED:
		{
			protocol.set_type(Protocol_Type_CALL_ACCEPTED);
			CallAccepted * obj = protocol.mutable_call_accepted();
			boost::shared_ptr<Call_Accepted> obj_ = boost::dynamic_pointer_cast<Call_Accepted>(pPackage);
			obj->set_id_emerg(obj_->IdEmergency);
			obj->set_id_reciever(obj_->IdReciever);
		}
		break;
	case Package::LST_MSG:
		{
			protocol.set_type(Protocol_Type_LST_MSG);
			LstMsg * obj = protocol.mutable_lst_msg();
			boost::shared_ptr<Lst_Msg> obj_ = boost::dynamic_pointer_cast<Lst_Msg>(pPackage);
			obj->set_id_vehicle(obj_->IdVehicle);
			obj->set_id_message(obj_->IdMessage);
		}
		break;
	case Package::VEHICLE_ALARM:		// vehicle.proto
		{
			protocol.set_type(Protocol_Type_VEHICLE_ALARM);
			VehicleAlarm * obj = protocol.mutable_vehicle_alarm();
			boost::shared_ptr<Vehicle_Alarm> obj_ = boost::dynamic_pointer_cast<Vehicle_Alarm>(pPackage);
			obj->set_id_vehicle(obj_->IdVehicle);
			obj->set_id_emerg(obj_->IdEmergency);
			obj->set_blue_light(obj_->BlueLight);
		}
		break;
	case Package::VEHICLE_STORNO:
		{
			protocol.set_type(Protocol_Type_VEHICLE_STORNO);
			VehicleStorno * obj = protocol.mutable_vehicle_stornno();
			boost::shared_ptr<Vehicle_Storno> obj_ = boost::dynamic_pointer_cast<Vehicle_Storno>(pPackage);
			obj->set_id_vehicle(obj_->IdVehicle);
			obj->set_id_emerg(obj_->IdEmergency);
		}
		break;
	case Package::VEHICLE_MSG:
		{
			protocol.set_type(Protocol_Type_VEHICLE_MSG);
			VehicleMsg * obj = protocol.mutable_vehicle_msg();
			boost::shared_ptr<Vehicle_Message> obj_ = boost::dynamic_pointer_cast<Vehicle_Message>(pPackage);
			obj->set_id_vehicle(obj_->IdVehicle);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::VEHICLE_UPDATE:
		{
			protocol.set_type(Protocol_Type_VEHICLE_UPDATE);
			VehicleUpdate * obj = protocol.mutable_vehicle_update();
			boost::shared_ptr<Vehicle_Update> obj_ = boost::dynamic_pointer_cast<Vehicle_Update>(pPackage);
			obj->set_id_vehicle(obj_->IdVehicle);
			obj->set_status((VehicleUpdate_VehicleStatus)obj_->Status);
			obj->set_destination_latitude(obj_->DestinationLatitude);
			obj->set_destination_longitude(obj_->DestinationLongitude);
			obj->set_id_emerg(obj_->IdEmergency);
			obj->set_id_patient(obj_->IdPatient);
			obj->set_blue_light(obj_->BlueLight);
		}
		break;
	case Package::VEHICLE_POSITION:
		{
			protocol.set_type(Protocol_Type_VEHICLE_POSITION);
			VehiclePosition * obj = protocol.mutable_vehicle_position();
			boost::shared_ptr<Vehicle_Position> obj_ = boost::dynamic_pointer_cast<Vehicle_Position>(pPackage);
			obj->set_id_vehicle(obj_->IdVehicle);
			obj->set_latitude(obj_->Latitude);
			obj->set_longitude(obj_->Longitude);
		}
		break;
	case Package::MSG_WALL:		// server.proto
		{
			protocol.set_type(Protocol_Type_MSG_WALL);
			MsgWall * obj = protocol.mutable_msg_wall();
			boost::shared_ptr<Message_Wall> obj_ = boost::dynamic_pointer_cast<Message_Wall>(pPackage);
			obj->set_id_sender(obj_->IdSender);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::MSG_CHAT:
		{
			protocol.set_type(Protocol_Type_MSG_CHAT);
			MsgChat * obj = protocol.mutable_msg_chat();
			boost::shared_ptr<Message_Chat> obj_ = boost::dynamic_pointer_cast<Message_Chat>(pPackage);
			obj->set_id_sender(obj_->IdSender);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::MSG_PRIVATE:
		{
			protocol.set_type(Protocol_Type_MSG_PRIVATE);
			MsgPrivate * obj = protocol.mutable_msg_private();
			boost::shared_ptr<Message_Private> obj_ = boost::dynamic_pointer_cast<Message_Private>(pPackage);
			obj->set_id_sender(obj_->IdSender);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::SERVER_WALL:
		{
			protocol.set_type(Protocol_Type_SERVER_WALL);
			ServerWall * obj = protocol.mutable_server_wall();
			boost::shared_ptr<Server_Wall> obj_ = boost::dynamic_pointer_cast<Server_Wall>(pPackage);
			obj->set_new_message(obj_->NewMessage);
		}
		break;
	case Package::USER_LOGIN_ANSWER:
		{
			protocol.set_type(Protocol_Type_USER_LOGIN_ANSWER);
			UserLoginAnswer * obj = protocol.mutable_user_login_answer();
			boost::shared_ptr<User_Login_Answer> obj_ = boost::dynamic_pointer_cast<User_Login_Answer>(pPackage);
			obj->set_servertime(obj_->Servertime);
		}
		break;
	case Package::USER_LIST_ANSWER:
		{
			protocol.set_type(Protocol_Type_USER_LIST_ANSWER);
			UserListAnswer * obj = protocol.mutable_user_list_answer();
			boost::shared_ptr<User_List_Answer> obj_ = boost::dynamic_pointer_cast<User_List_Answer>(pPackage);
			// todo!
			UNUSED(obj);
		}
		break;
	case Package::QUIT:
		{
			protocol.set_type(Protocol_Type_QUIT);
			protocol.mutable_quit();
		}
		break;
	}

	return protocol;
}

