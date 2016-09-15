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

#include <list>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

#include "CppSQLite3.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "SQL_Client.h"
#include "SQLite_Client.h"
#include "com_log/Log.h"
#include "com_convert/convert.h"

SQLite_Client::SQLite_Client(string Database)
	: SQL_Client(Database)
{
	try
	{
		mDBFile.open(Database.append(".sqlite").c_str());
	}
	catch (CppSQLite3Exception& e)
	{
		Log::GetInstance()->WriteError("SQLteError: " + string(e.errorMessage()) + ", Error Code: " + TToString(e.errorCode()));
	}
}

bool SQLite_Client::SendQueryNoReturn(const string & Query)
{
	try
	{
		mDBFile.execDML(Query.c_str());
		return true;
	}
	catch (CppSQLite3Exception& e)
	{
		Log::GetInstance()->WriteError("SQLteError: " + string(e.errorMessage()) + ", Error Code: " + TToString(e.errorCode()));
		Log::GetInstance()->WriteError("SQLteError: " + Query);
		return false;
	}
}

boost::shared_ptr<SQL_Result> SQLite_Client::SendQueryReturn(const string & Query)
{
	try
	{
		CppSQLite3Query results = mDBFile.execQuery(Query.c_str());
		return boost::shared_ptr<SQL_Result>(new SQLite_Result(results));
	}
	catch (CppSQLite3Exception& e)
	{
		Log::GetInstance()->WriteError("SQLteError: " + string(e.errorMessage()) + ", Error Code: " + TToString(e.errorCode()));
		Log::GetInstance()->WriteError("SQLteError: " + Query);
		return 0;
	}
}

SQLite_Client::~SQLite_Client()
{

}


SQLite_Result::SQLite_Result(const CppSQLite3Query & results)
	: mResults(results), mFirstNext(true)
{
}

bool SQLite_Result::next()
{
	if(mFirstNext)
	{
		mFirstNext = false;
	}
	else
	{
		mResults.nextRow();
	}
	return !mResults.eof();
}

int32_t SQLite_Result::getInt(uint32_t columnIndex)
{
	return mResults.getIntField(columnIndex);
}

int32_t SQLite_Result::getInt(string columnName)
{
	return mResults.getIntField(columnName.c_str());
}

string SQLite_Result::getString(uint32_t columnIndex)
{
	return mResults.getStringField(columnIndex);
}

string SQLite_Result::getString(string columnName)
{
	return mResults.getStringField(columnName.c_str());
}

long double SQLite_Result::getDouble(uint32_t columnIndex)
{
	return mResults.getFloatField(columnIndex);
}

long double SQLite_Result::getDouble(string columnName)
{
	return mResults.getFloatField(columnName.c_str());
}
