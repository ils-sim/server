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

#ifndef CLIENT_CONNECTION_H_
#define CLIENT_CONNECTION_H_

#include <boost/array.hpp>

#define MAX_DATA 512

class Client_Connection : public boost::enable_shared_from_this<Client_Connection>
{
public:
	Client_Connection(boost::asio::io_service & io_service, Server * server);

	void start();

	void handle_read_header(const boost::system::error_code & error);
	void handle_read_body(const boost::system::error_code & error);

	void do_close();

	boost::asio::ip::tcp::socket & socket();

	//void SetClient(Client client);
	Client & GetClient();
	bool IsConnectionClosed() const;

	void SendPackage(Protocol package);

private:
	void ProcessPackage(Protocol p);


	boost::asio::ip::tcp::socket mSocket;
	Client mClient;
	bool mConnectionClosed;
	std::vector<char> mData;
	Server * mpServer;
};


#endif
