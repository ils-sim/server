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
#include <map>
#include <string>

using namespace std;

#include "com_convert/convert.h"
#include "ini_reader.h"
#include "config.h"


bool config::readConfig(const string & filename, const string & sys)
{
	mSystem = sys;
	return reader.reload(filename);
}

int config::getTCPPort() const
{
	return reader.getInteger("General", "TCP_Port", 1244);
}

string config::getLogSetting() const
{
	return reader.getString(mSystem, "Log_Setting", "Debug");
}

bool config::getLogEchoToConsole() const
{
	return reader.getBoolean(mSystem, "Log_Echo", true);
}

string config::getLogfile() const
{
	return reader.getString(mSystem, "Log_File", mSystem + ".log");
}

string config::getDatabaseEngine() const
{
	return reader.getString("General", "Database_Engine", "SQLite");
}

string config::getDatabseMySQLServer() const
{
	return reader.getString("MySQL", "Server", "ils-sim.org");
}

string config::getDatabseMySQLUser() const
{
	return reader.getString("MySQL", "User", "NOUSER");
}

string config::getDatabseMySQLPassword() const
{
	return reader.getString("MySQL", "Password", "NOPASSWORD");
}

uint32_t config::getFahrzeugUID() const
{
	return (uint32_t)reader.getInteger("Fahrzeug", "UID", -1);
}

string config::getFahrzeugPassword() const
{
	return reader.getString("Fahrzeug", "Password", "NOPASSWORD");
}

uint32_t config::getEinsatzUID() const
{
	return (uint32_t)reader.getInteger("Einsatz", "UID", -1);
}

string config::getEinsatzPassword() const
{
	return reader.getString("Einsatz", "Password", "NOPASSWORD");
}

unsigned int config::getTestUserCount() const
{
	return (unsigned int)reader.getInteger("TestUser", "Count", 0);
}

uint32_t config::getTestUserUID(const int uid) const
{
	return (uint32_t)reader.getInteger("TestUser", "User" + TToString(uid) + "_UID", 0);
}

string config::getTestUserPassword(const int uid) const
{
	return reader.getString("TestUser", "User" + TToString(uid) + "_Password", "NOPASSWORD");
}


config::config()
{
}

config::~config()
{

}
