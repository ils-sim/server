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

#ifndef HOSPITAL_H_
#define HOSPITAL_H_

class Hospital
{
public:
	Hospital(uint32_t id, string name, Point position);

	uint32_t getId() const;
	string getName() const;
	Point getPosition() const;

private:
	const uint32_t mId;
	const string mName;
	const Point mPosition;
};

#include "com_shared/Singleton.templ"

class Hospital_Cache : public Singleton<Hospital_Cache>
{
	friend class Singleton<Hospital_Cache>;
public:
	Hospital searchClosestHospital(Point position) const;

private:
	Hospital_Cache();
	~Hospital_Cache();

	const list<Hospital> mHospitalList;
};


#endif

