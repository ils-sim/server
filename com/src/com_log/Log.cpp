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

#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

#include "com_convert/convert.h"

#if __WIN32__ || _MSC_VER
	#pragma warning( disable : 4996 )
#endif

#include "Log.h"

Log::Log()
	: mLogSetting(LogMessage), mEcho(true)
{
}

Log::~Log()
{
}

//cppcheck-suppress unusedFunction
void Log::SetFileName(const string & FileName)
{
	mFileName = FileName;
}

void Log::ChangeSetting(const string & newSetting)
{
	if(newSetting == "Debug")
	{
		mLogSetting = LogDebug;
	}
	else if(newSetting == "Message")
	{
		mLogSetting = LogMessage;
	}
	else if(newSetting == "Warning")
	{
		mLogSetting = LogWarning;
	}
	else if(newSetting == "Error")
	{
		mLogSetting = LogErrors;
	}
	else if(newSetting == "Panic")
	{
		mLogSetting = LogPanic;
	}
}

void Log::ChangeSetting(const LogSetting newSetting)
{
	mLogSetting = newSetting;
}

//cppcheck-suppress unusedFunction
void Log::EchoToConsole(const bool echo)
{
	mEcho = echo;
}

//cppcheck-suppress unusedFunction
void Log::WritePanic(const string & Msg)
{
	if(mLogSetting >= LogPanic)
	{
		Write("PANIC  ", Msg);
	}
}

void Log::WriteError(const string & Msg)
{
	if(mLogSetting >= LogErrors)
	{
		Write("ERROR  ", Msg);
	}
}

void Log::WriteWarning(const string & Msg)
{
	if(mLogSetting >= LogWarning)
	{
		Write("WARNING", Msg);
	}
}

void Log::WriteMessage(const string & Msg)
{
	if(mLogSetting >= LogMessage)
	{
		Write("MESSAGE", Msg);
	}
}

void Log::WriteDebug(const string & Msg)
{
	if(mLogSetting >= LogDebug)
	{
		Write("DEBUG  ", Msg);
	}
}

void Log::Write(const string & Typ, const string & Msg)
{
	time_t now = time(0);
	struct tm* tm = localtime(&now);

	std::stringstream time;
	time << setfill('0') << setw(2) << tm->tm_mday << '.' << setfill('0') << setw(2) << tm->tm_mon + 1 << '.' << (1900 + tm->tm_year)
		<< ' ' << setfill('0') << setw(2) << tm->tm_hour << ':' << setfill('0') << setw(2) << tm->tm_min << ':' << setfill('0') << setw(2) << tm->tm_sec << " : ";

	fstream FileStream(mFileName.c_str(), fstream::out | fstream::app);
	bool stream_is_open = FileStream.is_open();
	if(stream_is_open)
	{
		FileStream << time.str();
		FileStream << Typ << " : " << Msg << endl;
		FileStream.close();
	}
	if(mEcho || !stream_is_open)
	{
		cout << time.str();
		cout << Typ << " : " << Msg << endl;
	}
}


