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

#ifndef PACKAGE_EMERGENCIES_H_
#define PACKAGE_EMERGENCIES_H_

class Call_Accept : public Package
{
public:
	Call_Accept() : Package(Package::CALL_ACCEPT), IdEmergency(0) {}
	uint64_t IdEmergency;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdEmergency: " + TToString(IdEmergency);
	}
};

class Emergency_New : public Package
{
public:
	Emergency_New() : Package(Package::EMERG_NEW), IdEmergency(0) {}
	uint64_t IdEmergency;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdEmergency: " + TToString(IdEmergency);
	}
};

class Emergency_Update : public Package
{
public:
	Emergency_Update() : Package(Package::EMERG_UPDATE), IdEmergency(0) {}
	uint64_t IdEmergency;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdEmergency: " + TToString(IdEmergency);
	}
};

class Emergency_End : public Package
{
public:
	Emergency_End() : Package(Package::EMERG_END), IdEmergency(0) {}
	uint64_t IdEmergency;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdEmergency: " + TToString(IdEmergency);
	}
};

class Case_New : public Package
{
public:
	Case_New() : Package(Package::CASE_NEW), IdCase(0) {}
	uint64_t IdCase;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdCase: " + TToString(IdCase);
	}
};

class Case_Update : public Package
{
public:
	Case_Update() : Package(Package::CASE_UPDATE), IdCase(0) {}
	uint64_t IdCase;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdCase: " + TToString(IdCase);
	}
};

class Case_End : public Package
{
public:
	Case_End() : Package(Package::CASE_END), IdCase(0) {}
	uint64_t IdCase;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdCase: " + TToString(IdCase);
	}
};

class Call_Accepted : public Package
{
public:
	Call_Accepted() : Package(Package::CALL_ACCEPTED), IdEmergency(0), IdReciever(0) {}
	uint64_t IdEmergency;
	uint64_t IdReciever;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdEmergency: " + TToString(IdEmergency) + ", " +
			"IdReciever: " + TToString(IdReciever);
	}
};

class Lst_Msg : public Package
{
public:
	Lst_Msg() : Package(Package::LST_MSG), IdVehicle(0), IdMessage(0) {}
	uint32_t IdVehicle;
	uint32_t IdMessage;

	virtual string Package2String() const
	{
		return "Type: " + Type2String(GetType()) + ", " +
			"IdVehicle: " + TToString(IdVehicle) + ", " +
			"IdMessage: " + TToString(IdMessage);
	}
};

#endif