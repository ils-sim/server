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

#ifndef VEHICLE_AMB_H_
#define VEHICLE_AMB_H_

class Vehicle_Ambulance : public Abstract_Vehicle
{
public:
	Vehicle_Ambulance(const int Id, const string & Callsign, const Point & StationPosition);

	virtual void isStatusNichtEinsatzbereit();
	virtual void isStatusEinsatzbereit();
	virtual void isStatusEinsatzAkzeptiert();
	virtual void isStatusAnkunftEinsatzort();
	virtual void isStatusAbfahrtEinsatzort();
	virtual void isStatusAnkunftZielort();
	virtual void isStatusAbfahrtZielort();
	virtual void isStatusEintreffenDienststelle();
	virtual void isStatusFahrzeugBesetzen();
	virtual void isStatusPatientGefunden();

protected:
private:
};

#endif


