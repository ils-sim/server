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

#ifndef SERVER_INTERFACE_H_
#define SERVER_INTERFACE_H_

#include "com_package/Package.h"

class Server_Interface;

class Server_Observer
{
public:
	explicit Server_Observer(Server_Interface * interface);

	virtual bool Received_Package(Client & client, boost::shared_ptr<Package> pPackage) = 0;

protected:
	Server_Interface * GetInterface();

private:
	Server_Interface * mInterface;

};

class Server_Interface
{
public:
	Server_Interface();

	void Attache(Server_Observer * observer);

	virtual void SendToAll(boost::shared_ptr<Package> pPackage) = 0;
	virtual void SendToLSt(int32_t LSt, boost::shared_ptr<Package> pPackage) = 0;
	virtual void SendToUser(int32_t ToUid, boost::shared_ptr<Package> pPackage) = 0;

	bool Received_Package(Client & client, boost::shared_ptr<Package> pPackage);

private:
	vector<Server_Observer*> mObservers;
};


#endif