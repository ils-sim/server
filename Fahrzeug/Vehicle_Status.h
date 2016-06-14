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

#ifndef VEHICLE_STATUS_H_
#define VEHICLE_STATUS_H_

enum VehicleStatus
{
	NichtEinsatzbereit     = 1,
	Einsatzbereit          = 2,
	EinsatzAkzeptiert      = 3,
	AnkunftEinsatzort      = 4,
	AbfahrtEinsatzort      = 5,
	AnkunftZielort         = 6,
	AbfahrtZielort         = 7,
	EintreffenDienststelle = 8,
	FahrzeugBesetzen       = 9,
	PatientGefunden        = 10
};

string VehicleStatus2String(VehicleStatus status);

enum VehicleType
{
	RTW = 1,
	NEF = 2,
};

#endif