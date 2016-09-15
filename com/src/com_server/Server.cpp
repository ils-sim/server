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

#include "protocol.pb.h"
#include "com_convert/convert.h"
#include "com_log/Log.h"
#include "com_package/Package_Converter.h"
#include "Client.h"
#include "Server_Interface.h"
#include "Server.h"
#include "Client_Connection.h"

static Server * gServer;

Server::Server(boost::asio::io_service & io_service, const boost::asio::ip::tcp::endpoint & endpoint)
	: mIoService(io_service), mAcceptor(io_service, endpoint)
{
	start_accept();
	gServer = this;
}

//cppcheck -suppress unusedFunction
std::list<boost::shared_ptr<Client_Connection>> Server::GetConnectedClients() const
{
	return mConnections;
}

void Server::SendToAll(boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteDebug("Server::SendToAll");
	Protocol package = Package_Converter::Package2Protocol(pPackage);
	for(auto iter = mConnections.begin(); iter != mConnections.end(); iter++)
	{
		if((*iter)->GetClient().getUID() != -1)
		{
			(*iter)->SendPackage(package);
		}
	}
}

void Server::SendToLSt(int32_t LSt, boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteDebug("Server::SendToLSt");
	Protocol package = Package_Converter::Package2Protocol(pPackage);
	for(auto iter = mConnections.begin(); iter != mConnections.end(); iter++)
	{
		if((*iter)->GetClient().getIdLeitstelle() == LSt)
		{
			(*iter)->SendPackage(package);
		}
	}
}

void Server::SendToUser(int32_t ToUid, boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteDebug("Server::SendToUser");
	Protocol package = Package_Converter::Package2Protocol(pPackage);
	for(auto iter = mConnections.begin(); iter != mConnections.end(); iter++)
	{
		if((*iter)->GetClient().getUID() == ToUid)
		{
			(*iter)->SendPackage(package);
			return;
		}
	}
}

/*void Server::SendUserList()
{
	Log::GetInstance()->WriteDebug("Server::SendUserList");
}

void Server::SendUserList(int32_t ToUid)
{
	Log::GetInstance()->WriteDebug("Server::SendUserList");
}*/

void Server::start_accept()
{
	Log::GetInstance()->WriteMessage("Server::start_accept");
	boost::shared_ptr<Client_Connection> new_session(new Client_Connection(mIoService, this));
	mAcceptor.async_accept(new_session->socket(),
		boost::bind(&Server::handle_accept, this, new_session,
		boost::asio::placeholders::error));
}

void Server::handle_accept(boost::shared_ptr<Client_Connection> session, const boost::system::error_code & error)
{
	if (!error)
	{
		Log::GetInstance()->WriteMessage("Server::handle_accept");
		mConnections.push_back(session);
		session->start();
		mConnections.remove_if([] (boost::shared_ptr<Client_Connection> session) { return session->IsConnectionClosed(); });
	}
	else
	{
		Log::GetInstance()->WriteError("Server::handle_accept");
	}
	start_accept();
}

/*Server * GetServer()
{
	return gServer;
}*/
