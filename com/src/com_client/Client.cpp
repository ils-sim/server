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

using namespace std;

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

#include "protocol.pb.h"
#include "com_convert/convert.h"
#include "com_client/Client_Interface.h"
#include "com_client/Client.h"
#include "com_log/Log.h"
#include "com_package/Package_Converter.h"


Client::Client(boost::asio::io_service & io_service, tcp::resolver::iterator endpoint_iterator)
	: mIOService(io_service), mSocket(io_service)
{
	Log::GetInstance()->WriteDebug("Client::Client");
	boost::asio::async_connect(mSocket, endpoint_iterator,
		boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error)
	);
}

void Client::Send(boost::shared_ptr<Package> pPackage)
{
	Log::GetInstance()->WriteDebug("Client::Send");
	Protocol package = Package_Converter::Package2Protocol(pPackage);
	string output;
	package.SerializeToString(&output);

	std::vector<char> data;
	data.resize(4);
	uint32_t const size = output.size();
	*((uint32_t*)(&data[0])) = size;

	boost::system::error_code error;
	boost::asio::write(mSocket, boost::asio::buffer(data, 4), error);
	if (!error)
	{
		Log::GetInstance()->WriteDebug("Client::Send: OK");
	}
	else
	{
		Log::GetInstance()->WriteError("Client::Send::Header: NOT OK, " + error.message());
		doClose(Error);
		return;
	}

	boost::asio::write(mSocket, boost::asio::buffer(output), error);
	if (!error)
	{
		Log::GetInstance()->WriteDebug("Client::Send: OK");
	}
	else
	{
		Log::GetInstance()->WriteError("Client::Send::Body: NOT OK, " + error.message());
		doClose(Error);
	}
}

void Client::Close()
{
	Log::GetInstance()->WriteMessage("Client::Close");
	mIOService.post(boost::bind(&Client::doClose, this, NotConnected));
}

void Client::handle_connect(const boost::system::error_code& error)
{
	if (!error)
	{
		Log::GetInstance()->WriteMessage("Client::handle_connect: OK");
		isConnected = Connected;
		mData.resize(4);
		boost::asio::async_read(mSocket, boost::asio::buffer(mData, 4),
			boost::bind(&Client::handle_read_header, this, boost::asio::placeholders::error));
	}
	else
	{
		Log::GetInstance()->WriteError("Client::handle_connect: NOT OK, " + error.message());
		isConnected = Error;
	}
}

void Client::handle_read_header(const boost::system::error_code& error)
{
	if (!error)
	{
		Log::GetInstance()->WriteDebug("Client::handle_read_header: OK");
		int32_t size = *((uint32_t*)(&mData[0]));

		mData.resize(size);
		boost::asio::async_read(mSocket, boost::asio::buffer(mData, size),
			boost::bind(&Client::handle_read_body, this, boost::asio::placeholders::error));
	}
	else
	{
		Log::GetInstance()->WriteError("Client::handle_read_header: NOT OK, " + error.message());
		doClose(Error);
	}
}

void Client::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		Log::GetInstance()->WriteDebug("Client::handle_read_body: OK");
		Protocol CurrentProtocol;
		CurrentProtocol.ParseFromArray(&(mData[0]), mData.size());
		Log::GetInstance()->WriteMessage("Client_Connection::ProcessPackage: " + Protocol_Type_Name(CurrentProtocol.type()));
		boost::shared_ptr<Package> pPackage = Package_Converter::Protocol2Package(CurrentProtocol);
		Received_Package(pPackage);

		mData.resize(4);
		boost::asio::async_read(mSocket, boost::asio::buffer(mData, 4),
			boost::bind(&Client::handle_read_header, this, boost::asio::placeholders::error));
	}
	else
	{
		Log::GetInstance()->WriteError("Client::handle_read_body: NOT OK, " + error.message());
		doClose(Error);
	}
}

void Client::doClose(ConnectionStatus status)
{
	isConnected = status;
	Log::GetInstance()->WriteMessage("Client::doClose");
	boost::system::error_code ec;
	mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
	if(ec)
	{
		Log::GetInstance()->WriteError("Client::doClose: " + ec.message());
	}
	mSocket.close();
}

Client::~Client()
{
}
