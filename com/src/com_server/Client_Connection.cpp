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
#include <boost/array.hpp>

#include "protocol.pb.h"
#include "com_convert/convert.h"
#include "com_log/Log.h"
#include "com_package/Package_Converter.h"
#include "Client.h"
#include "Server.h"
#include "Client_Connection.h"
#include "Server_Interface.h"

Client_Connection::Client_Connection(boost::asio::io_service & io_service, Server * server)
	: mSocket(io_service)
{
	mConnectionClosed = false;
	mpServer = server;
}

void Client_Connection::start()
{
	Log::GetInstance()->WriteDebug("Client_Connection::start");
	mData.resize(4);
	boost::asio::async_read(mSocket, boost::asio::buffer(mData, 4),
		boost::bind(&Client_Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
}

void Client_Connection::handle_read_header(const boost::system::error_code & error)
{
	if(!error)
	{
		Log::GetInstance()->WriteDebug("Client_Connection::handle_read_header");
		int32_t size = *((uint32_t*)(&mData[0]));

		mData.resize(size);
		boost::asio::async_read(mSocket, boost::asio::buffer(mData, size),
			boost::bind(&Client_Connection::handle_read_body, shared_from_this(), boost::asio::placeholders::error));
	}
	else
	{
		Log::GetInstance()->WriteError("Client_Connection::handle_read_header: " + error.message());
		do_close();
	}
}

void Client_Connection::handle_read_body(const boost::system::error_code & error)
{
	if(!error)
	{
		Log::GetInstance()->WriteDebug("Client_Connection::handle_read_body");
		Protocol CurrentProtocol;
		CurrentProtocol.ParseFromArray(&(mData[0]), mData.size());
		ProcessPackage(CurrentProtocol);

		mData.resize(4);
		boost::asio::async_read(mSocket, boost::asio::buffer(mData, 4),
			boost::bind(&Client_Connection::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
	}
	else
	{
		Log::GetInstance()->WriteError("Client_Connection::handle_read_body: " + error.message());
		do_close();
	}
}

void Client_Connection::do_close()
{
	Log::GetInstance()->WriteMessage("Client_Connection::do_close");
	mConnectionClosed = true;
	mClient.setData(-1, -1);
	mSocket.close();
}

boost::asio::ip::tcp::socket & Client_Connection::socket()
{
	return mSocket;
}

/*void Client_Connection::SetClient(Client Client)
{
	mClient = Client;
}*/

Client & Client_Connection::GetClient()
{
	return mClient;
}

bool Client_Connection::IsConnectionClosed() const
{
	return mConnectionClosed;
}

void Client_Connection::SendPackage(Protocol package)
{
	Log::GetInstance()->WriteDebug("Client_Connection::SendPackage");
	string output;
	package.SerializeToString(&output);

	std::vector<char> data;
	data.resize(4);
	*((uint32_t*)(&data[0])) = output.size();

	boost::system::error_code error;
	boost::asio::write(mSocket, boost::asio::buffer(data, 4), error);
	if (!error)
	{
		Log::GetInstance()->WriteDebug("Client_Connection::SendPackage: OK");
	}
	else
	{
		Log::GetInstance()->WriteError("Client_Connection::SendPackage::Header: " + error.message());
		do_close();
		return;
	}

	boost::asio::write(mSocket, boost::asio::buffer(output), error);
	if (!error)
	{
		Log::GetInstance()->WriteDebug("Client_Connection::SendPackage: OK");
	}
	else
	{
		Log::GetInstance()->WriteError("Client_Connection::SendPackage::Header: " + error.message());
		do_close();
	}
}

void Client_Connection::ProcessPackage(Protocol p)
{
	Log::GetInstance()->WriteDebug("Client_Connection::ProcessPackage: " + Protocol_Type_Name(p.type()));
	/*if(p.type() == Protocol_Type_USER_LOGIN)
	{
		Log::GetInstance()->WriteMessage("UserLogin uid: " + TToString(p.user_login().uid()));
		Log::GetInstance()->WriteMessage("UserLogin control_center: " + TToString(p.user_login().control_center()));
		Log::GetInstance()->WriteMessage("UserLogin password: " + p.user_login().password());

		Protocol a;
		a.set_type(Protocol_Type_USER_LOGIN_ANSWER);
		UserLoginAnswer * login = a.mutable_user_login_answer();
		login->set_servertime(1234);
		SendPackage(a);
	}*/
	
	boost::shared_ptr<Package> pPackage = Package_Converter::Protocol2Package(p);
	if(GetClient().getUID() == -1 && pPackage->GetType() != Package::USER_LOGIN)
	{
		do_close();
		Log::GetInstance()->WriteWarning("Client_Connection::ProcessPackage: User not logged in! Baba :)");
		return;
	}
	if(!mpServer->Received_Package(GetClient(), pPackage))
	{
		do_close();
		Log::GetInstance()->WriteWarning("Client_Connection::ProcessPackage: User will be logged out! Baba :)");
	}
}
