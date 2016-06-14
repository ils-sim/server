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

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

using namespace std;

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Position.h"
#include "com_convert/convert.h"
//#include "com_log/Log.h"

Point::Point()
{
	mLong = 0.0;
	mLat = 0.0;
}

Point::Point(double Long, double Lat)
{
	mLong = Long;
	mLat = Lat;
}

/*void Point::Set(double Long, double Lat)
{
	mLong = Long;
	mLat = Lat;
}*/

/*void Point::SetZerro()
{
	mLong = 0.0;
	mLat = 0.0;
}*/

double Point::GetLong() const
{
	return mLong;
}

double Point::GetLat() const
{
	return mLat;
}

bool Point::isZerro() const
{
	return mLat == 0.0 && mLong == 0.0;
}

void Point::setZerro()
{
	mLat = 0.0;
	mLong = 0.0;
}

string Point::Print() const
{
	return "Lat: " + TToString(mLat) + ", Long: " + TToString(mLong);
}

bool Point::operator==(const Point & d) const
{
	if(d.GetLat() == this->GetLat() && d.GetLong() == this->GetLong())
	{
		return true;
	}
	return false;
}

#define EARTH_RADIUS_METER (6371000.0)
double Point::CalculateDistance(double Long1, double Lat1, double Long2, double Lat2)
{
	double lat1_rad = Lat1 * (M_PI / 180.0);
	double lat2_rad = Lat2 * (M_PI / 180.0);

	double delta_lat_rad = (Lat2 - Lat1) * (M_PI / 180.0);
	double delta_long_rad = (Long2 - Long1) * (M_PI / 180.0);

	double a = sin(delta_lat_rad / 2.0) * sin(delta_lat_rad / 2.0) +
		cos(lat1_rad) * cos(lat2_rad) *
		sin(delta_long_rad / 2.0) * sin (delta_long_rad / 2.0);
	double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
	double distance = EARTH_RADIUS_METER * c;
	return distance;
}

double Point::CalculateDistance(const Point & p1, const Point & p2)
{
	return CalculateDistance(p1.GetLong(), p1.GetLat(), p2.GetLong(), p2.GetLat());
}


Position::Position(double Long, double Lat, boost::posix_time::ptime timeAt)
	: Point(Long, Lat), mTimeAt(timeAt)
{

}

Position::Position(double Long, double Lat, const Position & LastPoint, double speed)
	: Point(Long, Lat)
{
	double dist = Point::CalculateDistance(LastPoint.GetLong(), LastPoint.GetLat(), Long, Lat);
	double new_time = dist / speed;
	mTimeAt = LastPoint.GetTimeAt() + boost::posix_time::milliseconds(uint64_t(new_time * 1000));
	//Log::GetInstance()->WriteDebug("distance: " + TToString(dist) + ", new_time: " + TToString(new_time) + ", time_at: " + TToString(mTimeAt));
}

boost::posix_time::ptime Position::GetTimeAt() const
{
	return mTimeAt;
}

string Position::Print() const
{
	return Point::Print() + ", Time at: " + TToString(mTimeAt);
}

bool Position::operator==(const Position & obj)
{
	return this->GetLat() == obj.GetLat() &&
		this->GetLong() == obj.GetLong() &&
		this->GetTimeAt() == obj.GetTimeAt();
}



