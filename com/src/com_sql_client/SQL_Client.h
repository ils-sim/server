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

#ifndef SQL_CLIENT_H_
#define SQL_CLIENT_H_

class SQL_Result
{
public:
	virtual bool next() = 0;

	virtual int32_t getInt(uint32_t columnIndex) = 0;
	virtual int32_t getInt(string columnName) = 0;
	virtual string getString(uint32_t columnIndex) = 0;
	virtual string getString(string columnName) = 0;
	virtual long double getDouble(uint32_t columnIndex) = 0;
	virtual long double getDouble(string columnName) = 0;

	virtual ~SQL_Result();
}; 

class SQL_Client
{
public:
	explicit SQL_Client(const string & database);

	virtual bool SendQueryNoReturn(const string & Query) = 0;
	virtual boost::shared_ptr<SQL_Result> SendQueryReturn(const string & Query) = 0;

	virtual string getDatabse() const;

	virtual ~SQL_Client();

private:
	string mDatabase;
};

boost::shared_ptr<SQL_Client> Generate_SQL_Client(const string & database);

/********************************************************************************************/

#include "com_shared/Singleton.templ"

class SQL_ClientGlobal : public Singleton<SQL_ClientGlobal>
{
	friend class Singleton<SQL_ClientGlobal>;
public:
	void AddNewInsertCommand(const string & query, const string & database);
	bool Process();
	//int CountQuerys() const;

private:
	SQL_ClientGlobal();
	~SQL_ClientGlobal();

	boost::shared_ptr<SQL_Client> getSQLDatabase(const string & database);

	list<std::pair<string, string>> InsertCommands;
	list<boost::shared_ptr<SQL_Client>> mSQLDatabase;
};

class SQL_ClientGlobalTask : public Task
{
public:
	SQL_ClientGlobalTask();
	virtual void run();
};

#endif
