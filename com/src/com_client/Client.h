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


#ifndef CLIENT_H_
#define CLIENT_H_

class Client : public Client_Interface
{
public:
	Client(boost::asio::io_service & io_service, tcp::resolver::iterator endpoint_iterator);

	void Send(boost::shared_ptr<Package> pPackage);

	void Close();

	virtual ~Client();

private:
	void handle_connect(const boost::system::error_code& error);
	void handle_read_header(const boost::system::error_code& error);
	void handle_read_body(const boost::system::error_code& error);
	void doClose(ConnectionStatus status = NotConnected);

	boost::asio::io_service & mIOService;
	tcp::socket mSocket;
	std::vector<char> mData;


	char msg_[255];
	char rec_msg_[255];
	uint32_t rec_leng_;

};

#endif


