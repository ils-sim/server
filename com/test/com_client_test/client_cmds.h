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

#ifndef CLIENT_CMDS_H_
#define CLIENT_CMDS_H_

class LoadScript_Cmd : public CLI_Command
{
public:
	explicit LoadScript_Cmd(CLI * pCli)
		: CLI_Command("load", "Ein Script laden welches dann ausgeführt wird."), mpCli(pCli), mPath("")
	{
	}

	virtual void Run(std::istream & stream)
	{
		string file_name = GetString("file", stream);
		RunScript(file_name);
	}

	void RunScript(string file_name)
	{
		std::ifstream file;
		file.open(mPath + file_name, std::ios_base::in);
		if(!file.good())
		{
			Log::GetInstance()->WriteError("File could not be loaded: " + file_name);
		}
		while(file.good())
		{
			mpCli->Loop(file);
		}
	}

	void SetPath(string path)
	{
		mPath = path;
	}

private:
	CLI * mpCli;
	string mPath;
};

class Sleep_Cmd : public CLI_Command
{
public:
	Sleep_Cmd()
		: CLI_Command("sleep", "Sleep x Sekunden.")
	{
	}

	virtual void Run(std::istream & stream)
	{
		int sec = GetInt("Sekunden", stream);
		boost::this_thread::sleep(boost::posix_time::seconds(sec));
	}
};

#endif
