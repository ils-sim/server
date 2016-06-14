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

#ifndef CLIENT_INTERFACE_H_
#define CLIENT_INTERFACE_H_

#include "com_package/Package.h"

class Client_Interface;

class Client_Observer
{
public:
	explicit Client_Observer(Client_Interface * interface);

	virtual void Received_Package(boost::shared_ptr<Package> pPackage) = 0;

	virtual ~Client_Observer();

protected:
	Client_Interface * GetInterface();

private:
	Client_Interface * mInterface;

};

enum ConnectionStatus
{
	NotConnected,
	Connected,
	Error,
};

class Client_Interface
{
public:
	Client_Interface();

	void Attache(Client_Observer * observer);

	virtual void Send(boost::shared_ptr<Package> pPackage) = 0;

	volatile ConnectionStatus isConnected;

	virtual ~Client_Interface();

protected:
	void Received_Package(boost::shared_ptr<Package> pPackage);

private:
	vector<Client_Observer*> mObservers;
};

#endif
