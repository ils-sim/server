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

#include <string>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <map>

using namespace std;

#include "com_log/Log.h"
#include "CppSQLite3.h"
#include "com_task_scheduler/Task_Scheduler.h"
#include "SQL_Client.h"
#include "SQLite_Client.h"
#include "MySQL_Client.h"
#include "com_config/ini_reader.h"
#include "com_config/config.h"

SQL_Result::~SQL_Result()
{

}

SQL_Client::~SQL_Client()
{

}


SQL_Client::SQL_Client(const string & database)
	: mDatabase(database)
{

}

string SQL_Client::getDatabse() const
{
	return mDatabase;
}

boost::shared_ptr<SQL_Client> Generate_SQL_Client(const string & database)
{
	string engine = config::GetInstance()->getDatabaseEngine();
	if(engine == "SQLite")
	{
		Log::GetInstance()->WriteDebug("Generate_SQL_Client: using SQLite");
		return boost::shared_ptr<SQL_Client>(new SQLite_Client(database));
	}
	else if(engine == "MySQL")
	{
		Log::GetInstance()->WriteDebug("Generate_SQL_Client: using MySQL");
		return boost::shared_ptr<SQL_Client>(new MySQL_Client(database));
	}
	else
	{
		Log::GetInstance()->WriteError("Generate_SQL_Client: wrong Engine! use: 'SQLite' or 'MySQL'!");
		return boost::shared_ptr<SQL_Client>();
	}
}

//***************************************************************

SQL_ClientGlobal::SQL_ClientGlobal()
{

}

SQL_ClientGlobal::~SQL_ClientGlobal()
{

}

void SQL_ClientGlobal::AddNewInsertCommand(const string & query, const string & database)
{
	InsertCommands.push_back(std::pair<string, string>(query, database));
}

bool SQL_ClientGlobal::Process()
{
	if(InsertCommands.empty())
	{
		return false;
	}
	list<std::pair<string, string>>::iterator iter = InsertCommands.begin();
	while (iter != InsertCommands.end())
	{
		boost::shared_ptr<SQL_Client> client = getSQLDatabase(iter->second);
		client->SendQueryNoReturn(iter->first);
		iter = InsertCommands.erase(iter);
	}
	return true;
}

/*int SQL_ClientGlobal::CountQuerys() const
{
	return InsertCommands.size();
}*/

boost::shared_ptr<SQL_Client> SQL_ClientGlobal::getSQLDatabase(const string & database)
{
	for(list<boost::shared_ptr<SQL_Client>>::iterator iter = mSQLDatabase.begin(); iter != mSQLDatabase.end(); ++iter)
	{
		if((*iter)->getDatabse() == database)
		{
			return (*iter);
		}
	}
	boost::shared_ptr<SQL_Client> connection = Generate_SQL_Client(database);
	mSQLDatabase.push_back(connection);
	return connection; 
}

SQL_ClientGlobalTask::SQL_ClientGlobalTask()
	: Task(Task::SQLPrio, "SQL_ClientGlobalTask")
{
	setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::millisec(500));
}

void SQL_ClientGlobalTask::run()
{
	SQL_ClientGlobal::GetInstance()->Process();
	setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::millisec(500));
}
