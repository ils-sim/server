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

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "com_convert/convert.h"
#include "com_server/Client.h"
#include "com_server/Server_Interface.h"
#include "com_server/Server.h"
#include "com_log/Log.h"

#include "Observer.h"

User_Observer::User_Observer(Server_Interface * interface)
	: Server_Observer(interface)
{
}

bool User_Observer::Received_Package(Client & client, boost::shared_ptr<Package> pPackage)
{
	switch(pPackage->GetType())
	{
	case Package::USER_CHAT:
		{
			boost::shared_ptr<User_Chat> chat = boost::dynamic_pointer_cast<User_Chat>(pPackage);
			boost::shared_ptr<Message_Chat> answer = boost::shared_ptr<Message_Chat>(new Message_Chat());
			answer->IdSender = client.getUID();
			answer->NewMessage = chat->NewMessage;
			GetInterface()->SendToLSt(client.getIdLeitstelle(), answer);
		}
		break;
	case Package::USER_LIST:
		// todo
		break;
	case Package::USER_LOGIN:
		{
			boost::shared_ptr<User_Login> login = boost::dynamic_pointer_cast<User_Login>(pPackage);
			if(Client::CheckUserPassword(login->UID, login->Password))
			{
				client.setData(login->UID, login->ControlCenter);
				boost::shared_ptr<User_Login_Answer> answer = boost::shared_ptr<User_Login_Answer>(new User_Login_Answer());
				answer->Servertime = 1234;
				GetInterface()->SendToUser(login->UID, answer);
			}
			else
			{
				return false;
			}
		}
		break;
	case Package::USER_LOGOUT:
		client.setData(-1, -1);
		break;
	case Package::USER_MSG:
		{
			boost::shared_ptr<User_Msg> chat = boost::dynamic_pointer_cast<User_Msg>(pPackage);
			boost::shared_ptr<Message_Private> answer = boost::shared_ptr<Message_Private>(new Message_Private());
			answer->IdSender = client.getUID();
			answer->NewMessage = chat->NewMessage;
			GetInterface()->SendToUser(chat->UIDReciever, answer);
		}
		break;
	case Package::USER_WALL:
		{
			boost::shared_ptr<User_Wall> chat = boost::dynamic_pointer_cast<User_Wall>(pPackage);
			boost::shared_ptr<Message_Wall> answer = boost::shared_ptr<Message_Wall>(new Message_Wall());
			answer->IdSender = client.getUID();
			answer->NewMessage = chat->NewMessage;
			GetInterface()->SendToAll(answer);
		}
		break;
	default:
		break;
	}
	return true;
}
