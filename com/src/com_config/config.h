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

#ifndef COM_CONFIG_H_
#define COM_CONFIG_H_

#include "com_shared/Singleton.templ"

class config : public Singleton<config>
{
	friend class Singleton<config>;
public:
	bool readConfig(const string & filename, const string & sys);

	int getTCPPort() const;

	string getLogSetting() const;
	bool getLogEchoToConsole() const;
	string getLogfile() const;

	string getDatabaseEngine() const;
	string getDatabseMySQLServer() const;
	string getDatabseMySQLUser() const;
	string getDatabseMySQLPassword() const;

	uint32_t getFahrzeugUID() const;
	string getFahrzeugPassword() const;

	uint32_t getEinsatzUID() const;
	string getEinsatzPassword() const;

	unsigned int getTestUserCount() const;
	uint32_t getTestUserUID(const int uid) const;
	string getTestUserPassword(const int uid) const;

private:
	config();
	~config();

	Init_Reader reader;
	string mSystem;
};

#endif