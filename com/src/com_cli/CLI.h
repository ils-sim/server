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

#ifndef CLI_H_
#define CLI_H_

class CLI_Command
{
public:
	CLI_Command(const string & cmdName, const string & description);
	
	string GetCmdName() const;

	virtual void Run(std::istream & stream) = 0;
	virtual void PrintHelp() const;

protected:
	string mCmdName;
	string mDescription;

	static int GetInt(const string & name, std::istream & stream, const int default_ = -1);
	static double GetDouble(const string & name, std::istream & stream, const double default_ = -1.0);
	static string GetString(const string & name, std::istream & stream, const string & default_ = "");
	static bool GetBool(const string & name, std::istream & stream, const bool default_ = false);
	static bool CheckInput();
};

class CLI
{
public:
	CLI();
	void AddCommand(boost::shared_ptr<CLI_Command> cmd);
	bool Loop(std::istream & stream) const;
	void PrintHelp() const;

private:
	list<boost::shared_ptr<CLI_Command>> mCommands;
};


#endif
