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

#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "com_shared/Singleton.templ"

class Log : public Singleton<Log>
{
	friend class Singleton<Log>;
public:
	enum LogSetting
	{
		LogPanic,
		LogErrors,
		LogWarning,
		LogMessage,
		LogDebug,
	};

	void SetFileName(const string & FileName);

	void ChangeSetting(const LogSetting newSetting);
	void ChangeSetting(const string & newSetting);
	void EchoToConsole(const bool echo);

	void WritePanic(const string & Msg);
	void WriteError(const string & Msg);
	void WriteWarning(const string & Msg);
	void WriteMessage(const string & Msg);
	void WriteDebug(const string & Msg);

	void Write(const string & Typ, const string & Msg);

private:
	Log();
	~Log();

	LogSetting mLogSetting;
	bool mEcho;

	string mFileName;
};

#endif
