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

#ifndef MYSQL_CLIENT_H_
#define MYSQL_CLIENT_H_

class MySQL_Client : public SQL_Client
{
public:
	explicit MySQL_Client(const string & Database);
	
	virtual bool SendQueryNoReturn(const string & Query);
	virtual boost::shared_ptr<SQL_Result> SendQueryReturn(const string & Query);

	virtual ~MySQL_Client();
private:
	const string mServer;
	const string mUser;
	const string mPassword;
	const string mDatabase;
	sql::Driver * mDriver;
	boost::shared_ptr<sql::Connection> mConnection;
};

class MySQL_Result : public SQL_Result
{
public:
	explicit MySQL_Result(boost::shared_ptr<sql::ResultSet> results);

	virtual bool next();

	virtual int32_t getInt(uint32_t columnIndex);
	virtual int32_t getInt(string columnName);
	virtual string getString(uint32_t columnIndex);
	virtual string getString(string columnName);
	virtual long double getDouble(uint32_t columnIndex);
	virtual long double getDouble(string columnName);

private:
	boost::shared_ptr<sql::ResultSet> mResults;
};




#endif
