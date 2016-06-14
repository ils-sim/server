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

/*#include <iostream>
#include <string>
#include <list>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

#include "com_task_scheduler/Task_Scheduler.h"
#include "com_sql_client/SQL_Client.h"
#include "com_log/Log.h"
#include "com_convert/convert.h"
#include "Patient.h"


Patient::Patient(unsigned int id, bool isDead, PatientPosition position)
{
	mId = id;
	mIsDead = isDead;
	mPosition = position;
}

unsigned int Patient::getId() const
{
	return mId;
}

bool Patient::isDead() const
{
	return mIsDead;
}

PatientPosition Patient::getPosition() const
{
	return mPosition;
}

void Patient::died()
{
	mIsDead = true;
	string str = "UPDATE  `online_ilssim`.`Patient` SET  `Tot` =  '1' ";
	str += "WHERE  `Patient`.`idPatient` = " + TToString(mId) + ";";
	MySQL_ClientGlobal::GetInstance()->AddNewInsertCommand(str);
}

void Patient::changePosition(PatientPosition newPosition)
{
	mPosition = newPosition;
	string str = "UPDATE  `online_ilssim`.`Patient` SET  `PatientenStandort_idPatientenStandort` =  '" + TToString(mPosition) + "' ";
	str += "WHERE  `Patient`.`idPatient` = " + TToString(mId) + ";";
	MySQL_ClientGlobal::GetInstance()->AddNewInsertCommand(str);
}
*/