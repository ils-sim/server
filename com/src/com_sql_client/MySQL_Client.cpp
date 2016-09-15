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
#include <map>

#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

#include "com_task_scheduler/Task_Scheduler.h"
#include "SQL_Client.h"
#include "MySQL_Client.h"
#include "com_log/Log.h"
#include "com_convert/convert.h"
#include "com_config/ini_reader.h"
#include "com_config/config.h"

//#define MYSQL_SERVER	"localhost"
#define MYSQL_SERVER	"ils-sim.org"
#define MYSQL_USER		"gameuser"
#define MYSQL_PASS		"d4c3m8bXNXRrJzDK"

MySQL_Client::MySQL_Client(const string & Database)
	: SQL_Client(Database), mServer(config::GetInstance()->getDatabseMySQLServer()), mUser(config::GetInstance()->getDatabseMySQLUser()),
	mPassword(config::GetInstance()->getDatabseMySQLPassword()), mDatabase(Database)
{
	try
	{
		mDriver = get_driver_instance();
		mConnection.reset(mDriver->connect(mServer, mUser, mPassword));
		mConnection->setSchema(mDatabase);
	}
	catch (sql::SQLException & e)
	{
		Log::GetInstance()->WriteError("MySQLError: " + string(e.what()) + ", Error Code: " + TToString(e.getErrorCode()) + ", State: " + string(e.getSQLState()));
	}
}

bool MySQL_Client::SendQueryNoReturn(const string & Query)
{
	try
	{
		boost::shared_ptr<sql::Statement> statment(mConnection->createStatement());
		statment->execute(Query);
		return true;
	}
	catch (sql::SQLException & e)
	{
		Log::GetInstance()->WriteError("MySQLError: " + string(e.what()) + ", Error Code: " + TToString(e.getErrorCode()) + ", State: " + string(e.getSQLState()));
		Log::GetInstance()->WriteError("MySQL Query: '" + Query + "'");
		return false;
	}
}

boost::shared_ptr<SQL_Result> MySQL_Client::SendQueryReturn(const string & Query)
{
	try
	{
		Log::GetInstance()->WriteDebug("MySQL Query: " + Query);
		boost::shared_ptr<sql::PreparedStatement> statment(mConnection->prepareStatement(Query));
		return boost::shared_ptr<SQL_Result>(new MySQL_Result(boost::shared_ptr<sql::ResultSet>(statment->executeQuery())));
	}
	catch (sql::SQLException & e)
	{
		Log::GetInstance()->WriteError("MySQLError: " + string(e.what()) + ", Error Code: " + TToString(e.getErrorCode()) + ", State: " + string(e.getSQLState()));
		Log::GetInstance()->WriteError("MySQL Query: '" + Query + "'");
		return 0;
	}
}

MySQL_Client::~MySQL_Client()
{

}

//***************************************************************

MySQL_Result::MySQL_Result(boost::shared_ptr<sql::ResultSet> results)
	: mResults(results)
{
}

bool MySQL_Result::next()
{
	return mResults->next();
}

int32_t MySQL_Result::getInt(uint32_t columnIndex)
{
	return mResults->getInt(columnIndex + 1);
}

int32_t MySQL_Result::getInt(string columnName)
{
	return mResults->getInt(columnName);
}

string MySQL_Result::getString(uint32_t columnIndex)
{
	return mResults->getString(columnIndex + 1);
}

string MySQL_Result::getString(string columnName)
{
	return mResults->getString(columnName);
}

long double MySQL_Result::getDouble(uint32_t columnIndex)
{
	return mResults->getDouble(columnIndex + 1);
}

long double MySQL_Result::getDouble(string columnName)
{
	return mResults->getDouble(columnName);
}
