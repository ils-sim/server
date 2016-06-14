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

#ifndef OBSERVER_H_
#define OBSERVER_H_

class Echo_Observer : public Client_Observer
{
public:
	explicit Echo_Observer(Client_Interface * interface);
	virtual void Received_Package(boost::shared_ptr<Package> pPackage);
};

class Emergencies_Observer : public Client_Observer
{
public:
	explicit Emergencies_Observer(Client_Interface * interface);
	virtual void Received_Package(boost::shared_ptr<Package> pPackage);
};

class cServer_Observer : public Client_Observer
{
public:
	explicit cServer_Observer(Client_Interface * interface);
	virtual void Received_Package(boost::shared_ptr<Package> pPackage);
};

class User_Observer : public Client_Observer
{
public:
	explicit User_Observer(Client_Interface * interface);
	virtual void Received_Package(boost::shared_ptr<Package> pPackage);
};

class Vehicle_Observer : public Client_Observer
{
public:
	explicit Vehicle_Observer(Client_Interface * interface);
	virtual void Received_Package(boost::shared_ptr<Package> pPackage);
};

#endif
