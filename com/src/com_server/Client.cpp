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

#include <map>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
using boost::asio::ip::tcp;

#include <string>
using namespace std;

#include "Client.h"
//#include "Shared/mysql_client.h"
#include "com_convert/convert.h"
#include "com_log/Log.h"
#include "com_config/ini_reader.h"
#include "com_config/config.h"

Client::Client()
{
	mUID = -1;
	mIdLeitstelle = -1;
}

void Client::setData(const uint32_t uid, const uint32_t idLeitstelle)
{
	mUID = uid;
	mIdLeitstelle = idLeitstelle;
}

int32_t Client::getUID() const
{
	return mUID;
}

int32_t Client::getIdLeitstelle() const
{
	return mIdLeitstelle;
}

bool Client::CheckUserPassword(uint32_t uid, string password)
{
	Log::GetInstance()->WriteMessage("Client::CheckUserPassword: Lets check the user");
	Log::GetInstance()->WriteMessage(TToString(uid));
	Log::GetInstance()->WriteDebug(password);
	if(uid == config::GetInstance()->getEinsatzUID() && password == config::GetInstance()->getEinsatzPassword()) // Einsatz-Server
	{
		return true;
	}
	else if(uid == config::GetInstance()->getFahrzeugUID() && password == config::GetInstance()->getFahrzeugPassword()) // Fahrzeug-Server
	{
		return true;
	}
	for(unsigned int i = 0; i < config::GetInstance()->getTestUserCount(); ++i)
	{
		if(uid == config::GetInstance()->getTestUserUID(i) && password == config::GetInstance()->getTestUserPassword(i))
		{
			return true;
		}
	}

	/*MySQL_Client Client("ils-sim.org");
	string str = "SELECT TRUE FROM  `mybb_users` WHERE uid = " + TToString(uid) + " AND PASSWORD = MD5('" + WStringToString(password) + "');";
	if(!Client.SendSQLQuery(str))
	{
		return false; // MySQL Server error
	}
	MYSQL_RES * data = Client.GetResult();
	MYSQL_ROW row;
	bool passwordWrong = true;
	while((row = mysql_fetch_row(data)) != 0)
	{
		passwordWrong = false;
	}
	return !passwordWrong;*/
	return false;
}
