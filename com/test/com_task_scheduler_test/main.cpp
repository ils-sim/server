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

#if defined(__WIN32__) || defined(_MSC_VER)
#include <Windows.h>
#endif

using namespace std;

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "com_task_scheduler/Task_Scheduler.h"
#include "com_http_client/Http_Client.h"
#include "com_log/Log.h"

void test_1(void);
void test_2(void);
void test_3(void);

boost::shared_ptr<ThreadSaveQueue<boost::shared_ptr<Task>>> inputQueue(new ThreadSaveQueue<boost::shared_ptr<Task>>);

int main(int argc, char ** argv)
{
#ifdef _DEBUG
	Log::GetInstance()->ChangeSetting(Log::LogDebug);
#endif
	srand((unsigned int)time(0));
	test_1();
	test_2();
	test_3();
}



class WorkerTask_1 : public Task
{
public:
	explicit WorkerTask_1(unsigned int nr)
		: Task(RunnerPrio, "WorkerTask_1")
	{
		mNr = nr;
	}

	virtual void run()
	{
		cout << "Hello i am worker " << mNr << endl;
		setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::millisec(rand() % 5000));
	}

private:
	unsigned int mNr;
};

void create_tasks_1()
{
	for(int i = 0; i < 100; i++)
	{
		inputQueue->push(boost::shared_ptr<Task>(new WorkerTask_1(i)));
		//Sleep(1000);
	}
	cout << "Worker done" << endl;
}

void test_1(void)
{
	TaskScheduler scheduler(inputQueue);
	boost::thread worker(create_tasks_1);
	scheduler.Run();
}


class WorkerTask_2 : public Task
{
public:
	WorkerTask_2(unsigned int nr, TaskPriority prio)
		: Task(prio, "WorkerTask_2")
	{
		mNr = nr;
	}

	virtual void run()
	{
		cout << "Hello i am worker: " << mNr << " with Prio: " << getPriority() << endl;
		setNextRuntime(boost::posix_time::microsec_clock::universal_time() + boost::posix_time::seconds(100));
	}

private:
	unsigned int mNr;
};

void test_2(void)
{
	TaskScheduler scheduler(inputQueue);
	inputQueue->push(boost::shared_ptr<Task>(new WorkerTask_2(3, Task::TXPrio)));
	inputQueue->push(boost::shared_ptr<Task>(new WorkerTask_2(2, Task::SQLPrio)));
	inputQueue->push(boost::shared_ptr<Task>(new WorkerTask_2(1, Task::RunnerPrio)));
	inputQueue->push(boost::shared_ptr<Task>(new WorkerTask_2(0, Task::RXPrio)));
	scheduler.Run();
}


void test_3(void)
{
	stringstream url;
	url << "/api/1.0/gosmore.php?format=kml"
		<< "&flat=" << "48.3197341"
		<< "&flon=" << "14.3385475"
		<< "&tlat=" << "48.32798"
		<< "&tlon=" << "14.3254067"
		<< "&v=motorcar&fast=1&layer=mapnik";

	string data;
	HttpClient::getHttpData("yournavigation.org", url.str(), data);

	cout << "data: " << data << endl;
}
