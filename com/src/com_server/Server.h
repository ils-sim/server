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

#ifndef SERVER_H_
#define SERVER_H_

class Client_Connection;
class Protocol;

#include "Server_Interface.h"

class Server : public Server_Interface
{
public:
	Server(boost::asio::io_service & io_service, const boost::asio::ip::tcp::endpoint & endpoint);

	std::list<boost::shared_ptr<Client_Connection>> GetConnectedClients() const;

	virtual void SendToAll(boost::shared_ptr<Package> pPackage);
	virtual void SendToLSt(int32_t LSt, boost::shared_ptr<Package> pPackage);
	virtual void SendToUser(int32_t ToUid, boost::shared_ptr<Package> pPackage);

	//void SendUserList();
	//void SendUserList(int32_t ToUid);

private:
	void start_accept();

	void handle_accept(boost::shared_ptr<Client_Connection> session, const boost::system::error_code & error);

	boost::asio::io_service & mIoService;
	boost::asio::ip::tcp::acceptor mAcceptor;

	std::list<boost::shared_ptr<Client_Connection>> mConnections;
};

//Server * GetServer();

#endif
