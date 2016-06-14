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

#include <string>

using namespace std;

#include "Vehicle_Status.h"

string VehicleStatus2String(VehicleStatus status)
{
	switch(status)
	{
	case NichtEinsatzbereit:
		return "Nicht Einsatzbereit";
	case Einsatzbereit:
		return "Einsatzbereit";
	case EinsatzAkzeptiert:
		return "Einsatz Akzeptiert";
	case AnkunftEinsatzort:
		return "Ankunft Einsatzort";
	case AbfahrtEinsatzort:
		return "Abfahrt Einsatzort";
	case AnkunftZielort:
		return "Ankunft Zielort";
	case AbfahrtZielort:
		return "Abfahrt Zielort";
	case EintreffenDienststelle:
		return "Eintreffen Dienststelle";
	case FahrzeugBesetzen:
		return "Fahrzeug Besetzen";
	case PatientGefunden:
		return "Patient Gefunden";
	default:
		return "";
	}
}
