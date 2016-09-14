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

#ifndef TASK_SCHEDULER_H_
#define TASK_SCHEDULER_H_


class Task
{
public:
	enum TaskPriority
	{
		RXPrio = 0,
		RunnerPrio = 1,
		SQLPrio = 2,
		TXPrio = 3,
	};

	Task(TaskPriority prio, const string & TaskName);

	virtual void run() = 0;

	boost::posix_time::ptime getNextRuntime() const;
	void setNextRuntime(boost::posix_time::ptime next);

	TaskPriority getPriority() const;

	string getName() const;

private:
	boost::posix_time::ptime mNextRuntime;
	TaskPriority mPriority;
	const string mTaskName;
};

#include "com_shared/Thread_Save_Queue.templ"

class TaskScheduler
{
public:
	TaskScheduler(boost::shared_ptr<ThreadSaveQueue<boost::shared_ptr<Task>>> inputQueue, unsigned int timeout_ms = 100);

	void Run();
	//void SetTimeout(unsigned int ms);

private:
	void AddNewTasks();
	void SortTasks();
	bool RunNextTask();
	void Wait();

	list<boost::shared_ptr<Task>> mTaskList;
	boost::shared_ptr<ThreadSaveQueue<boost::shared_ptr<Task>>> mInputQueue;
	unsigned int mTimeout;
};

#endif
