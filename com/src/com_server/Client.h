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

#ifndef CLIENT_H_
#define CLIENT_H_

#define EinsatzServer	0x0FFF0001  // 268369921
#define FahrzeugServer	0x0FFF0002  // 268369922
#define TestUser0		0x0FFF0003  // 268369923
#define TestUser1		0x0FFF0004  // 268369924

class Client
{
public:
	Client();

	void setData(const uint32_t uid, const uint32_t idLeitstelle);

	int32_t getUID() const;
	int32_t getIdLeitstelle() const;

	static bool CheckUserPassword(uint32_t uid, string password);

private:
	int32_t mIdLeitstelle;
	int32_t mUID;
};

#endif
