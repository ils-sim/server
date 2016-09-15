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

#include <list>
#if __unix__  || __linux__
#include <unistd.h>
#define Sleep usleep
#elif __WIN32__ || _MSC_VER
#include <Windows.h>
#endif

using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "com_log/Log.h"
#include "com_shared/Thread_Save_Queue.templ"
#include "Task_Scheduler.h"

Task::Task(TaskPriority prio, const string & TaskName)
	: mPriority(prio), mTaskName(TaskName)
{
	setNextRuntime(boost::posix_time::microsec_clock::universal_time());
}

boost::posix_time::ptime Task::getNextRuntime() const
{
	return mNextRuntime;
}

void Task::setNextRuntime(boost::posix_time::ptime next)
{
	Log::GetInstance()->WriteDebug("Task::setNextRuntime, " + getName() + ": Current: " + to_simple_string(boost::posix_time::microsec_clock::universal_time()) + ", NextRuntime: " + to_simple_string(next));
	mNextRuntime = next;
}

Task::TaskPriority Task::getPriority() const
{
	return mPriority;
}

string Task::getName() const
{
	return mTaskName;
}

class Criterium
{
public:
	bool operator() (Task const * const task1, Task const * const task2) const
	{
		return task1->getNextRuntime() < task2->getNextRuntime();
	}
};


TaskScheduler::TaskScheduler(boost::shared_ptr<ThreadSaveQueue<boost::shared_ptr<Task>>> inputQueue, unsigned int timeout_ms)
{
	mInputQueue = inputQueue;
	mTimeout = timeout_ms;
}

void TaskScheduler::Run()
{
	while(true)
	{
		AddNewTasks();
		SortTasks();
		if(!RunNextTask())
		{
			Wait();
		}
	}
}

/*void TaskScheduler::SetTimeout(unsigned int ms)
{
	mTimeout = ms;
}*/

void TaskScheduler::AddNewTasks()
{
	while(!mInputQueue->empty())
	{
		mTaskList.push_back(mInputQueue->front());
		mInputQueue->pop();
	}
}

void TaskScheduler::SortTasks()
{
	Criterium criterium;
	mTaskList.sort(
		[&criterium] (const boost::shared_ptr<Task> & l, const boost::shared_ptr<Task> & r)
		{
			return criterium(l.get(), r.get());
		});
}

bool TaskScheduler::RunNextTask()
{
	if(mTaskList.empty())
	{
		return false;
	}
	boost::posix_time::ptime utc = boost::posix_time::microsec_clock::universal_time();
	if((*mTaskList.begin())->getNextRuntime() <= utc)
	{
		Log::GetInstance()->WriteDebug((*mTaskList.begin())->getName() + ": UTC: " + to_simple_string(utc) + ", NextRuntime: " + to_simple_string((*mTaskList.begin())->getNextRuntime()));
		(*mTaskList.begin())->run();
		return true;
	}
	return false;
}

void TaskScheduler::Wait()
{
	Sleep(mTimeout);
}
