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

#ifndef ROUTE_H_
#define ROUTE_H_

class Route : public list<Position>
{
public:
	Route(Position start, Point end, double speed);

	//list<Position>::const_iterator begin() const;
	//list<Position>::const_iterator end() const;

	double GetTotalDistance() const;

	void debug() const;

private:
	//list<Position> mPositionList;
	double mTotalDistance;

	bool parse_server(const string & data, double speed);
	void FilterRoute();
	void CalculateDistance();
	static Position ExportPoint(const string & data, const Position & lastPoint, double speed);
};

//void removeDoubleElems(list<CarWay> & liste);
//void filter2sec(list<CarWay> & liste);

#endif
