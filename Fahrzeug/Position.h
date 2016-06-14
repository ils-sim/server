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

#ifndef POSITION_H_
#define POSITION_H_

class Point
{
public:
	Point();
	Point(double Long, double Lat);

	//void Set(double Long, double Lat);
	//void SetZerro();

	double GetLong() const;
	double GetLat() const;

	bool isZerro() const;
	void setZerro();

	virtual string Print() const;

	bool operator==(const Point & d) const;

	// return value in m (Meter)
	static double CalculateDistance(double Long1, double Lat1, double Long2, double Lat2);
	static double CalculateDistance(const Point & p1, const Point & p2);

private:
	double mLong;
	double mLat;
};

class Position : public Point
{
public:
	Position(double Long, double Lat, boost::posix_time::ptime timeAt);
	Position(double Long, double Lat, const Position & LastPoint, double speed); // speed in m/s

	boost::posix_time::ptime GetTimeAt() const;

	virtual string Print() const;

	bool operator==(const Position & obj);

private:
	boost::posix_time::ptime mTimeAt;
};

Point ExportPoint(const string & data);

#endif