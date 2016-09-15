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
#include <sstream>
#include <list>

using namespace std;

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Position.h"
#include "Route.h"
#include "com_http_client/Http_Client.h"
#include "com_log/Log.h"
#include "com_convert/convert.h"

//const static string ROUTE_SERVER = "localhost";
const static string ROUTE_SERVER = "yournavigation.org";

Route::Route(const Position & start, const Point & end, const double speed)
	: mTotalDistance(0)
{
	push_back(start);

	stringstream url;
	url << "/api/1.0/gosmore.php?format=kml"
		<< "&flat=" << start.GetLat()
		<< "&flon=" << start.GetLong()
		<< "&tlat=" << end.GetLat()
		<< "&tlon=" << end.GetLong()
		<< "&v=motorcar&fast=1&layer=mapnik";
	//cout << url.str() << endl;

	Log::GetInstance()->WriteDebug("Route url: " + url.str());

	string data;
	if(!HttpClient::getHttpData(ROUTE_SERVER, url.str(), data))
	{
		Log::GetInstance()->WriteError("HTTP Server error, could not get a Route from server...");
		Log::GetInstance()->WriteError("will try to calculate direct route....");
		push_back(Position(end.GetLong(), end.GetLat(), *cend(), speed));
	}
	else
	{
		parse_server(data, speed);
		FilterRoute();
		CalculateDistance();
		Log::GetInstance()->WriteMessage("Distance is: " + TToString(GetTotalDistance()));
	}
}

double Route::GetTotalDistance() const
{
	return mTotalDistance;
}

void Route::debug() const
{
	Log::GetInstance()->WriteDebug("Route debug:");
	for(list<Position>::const_iterator iter = this->begin(); iter != this->end(); ++iter)
	{
		Log::GetInstance()->WriteDebug("  " + to_simple_string(iter->GetTimeAt()) + ", Lat: " + TToString(iter->GetLat()) + ", Long: " + TToString(iter->GetLong()));
	}
}

bool Route::parse_server(const string & data, const double speed)
{
	stringstream workdata;
	workdata << data;

	string line;
	bool found = false;
	while(!workdata.eof())
	{
		getline(workdata, line);
		stringstream linedata;
		linedata << line;
		linedata.ignore();
		string left;
		linedata >> left;
		if(left == "<coordinates>")
		{
			linedata >> left;
			push_back(ExportPoint(left, *rbegin(), speed));
			found = true;
		}
		else if(left == "</coordinates>")
		{
			return true;
		}
		else if(found)
		{
			push_back(ExportPoint(line, *rbegin(), speed));
		}
	}
	return false;
}

void Route::FilterRoute()
{
	Log::GetInstance()->WriteDebug("route: ");
	list<Position> temp;
	temp.push_back(*begin());
	list<Position>::reverse_iterator last_insert = temp.rbegin();
	for(list<Position>::iterator iter = this->begin(); iter != this->end(); ++iter)
	{
		Log::GetInstance()->WriteDebug(to_simple_string(last_insert->GetTimeAt()) + " . " + to_simple_string(iter->GetTimeAt()));
		if(iter->GetTimeAt() - last_insert->GetTimeAt() > boost::posix_time::seconds(2))
		{
			Log::GetInstance()->WriteDebug(to_simple_string(last_insert->GetTimeAt()) + " - " + to_simple_string(iter->GetTimeAt()));
			temp.push_back(*iter);
			last_insert = temp.rbegin();
		}
	}
	this->clear();
	this->insert(this->begin(), temp.begin(), temp.end());
}

void Route::CalculateDistance()
{
	mTotalDistance = 0.0;
	for(list<Position>::const_iterator iter = cbegin(); iter != end(); ++iter)
	{
		list<Position>::const_iterator next = iter;
		++next;
		if(next != cend())
		{
			double distance = Point::CalculateDistance(*iter, *next);
			//cout << "distance: " << distance << " lat1: " << iter->GetLat() << ", long1: " << iter->GetLong() << ", lat2: " << next->GetLat() << ", long2: " << next->GetLong() << endl;
			 mTotalDistance += distance;
		}
	}
}

Position Route::ExportPoint(const string & data, const Position & lastPoint, const double speed)
{
	std::stringstream exported;
	double Lat = 0.0;
	double Long = 0.0;
	for(size_t i = 0; i < data.length(); i++)
	{
		if(data[i] == ',')
		{
			exported >> Long;
			exported.clear();
		}
		else
		{
			exported << data[i];
		}
	}
	exported >> Lat;
	return Position(Long, Lat, lastPoint, speed);
}


