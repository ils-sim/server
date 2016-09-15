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

#ifndef SQLITE_CLIENT_H_
#define SQLITE_CLIENT_H_

class SQLite_Client : public SQL_Client
{
public:
	explicit SQLite_Client(string Database);

	virtual bool SendQueryNoReturn(const string & Query);
	virtual boost::shared_ptr<SQL_Result> SendQueryReturn(const string & Query);

	virtual ~SQLite_Client();
private:
	const string mDatabase;
	CppSQLite3DB mDBFile;
};

class SQLite_Result : public SQL_Result
{
public:
	explicit SQLite_Result(const CppSQLite3Query & results);

	virtual bool next();

	virtual int32_t getInt(uint32_t columnIndex);
	virtual int32_t getInt(string columnName);
	virtual string getString(uint32_t columnIndex);
	virtual string getString(string columnName);
	virtual long double getDouble(uint32_t columnIndex);
	virtual long double getDouble(string columnName);

private:
	CppSQLite3Query mResults;
	bool mFirstNext;
};

#endif
