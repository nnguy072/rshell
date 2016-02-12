#include "Parser.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <string.h>
#include "Executer.h"
using namespace std;

Parser::~Parser()
{
	// nothing
}

void Parser::setCommand(string &c)
{
	command = c;
}

void Parser::parse()
{
	vector<string> temp;
	string temp2;
	unsigned int i = 0;				// keeps track of for loop inside
	unsigned int k = 0;				// keeps track of while loop
	
	// to add more conectors in the future
	// add on to this list
	bool isSemiColon = false;
	bool isLine = false;
	bool isAmpersand = false;
	// parse command using boost library
	boost::split(temp, command, boost::is_any_of(" "));

	// find the comment
	int numToRemove = 0;
	bool comment = false;
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		// if # is found
		if(temp[i] == ("#"))
		{
			numToRemove = temp.size() - i;
			break;
		}
		else if(temp[i].find("#") != string::npos)
		{
			if(temp[i].at(0) == '#')
			{
				numToRemove = temp.size() - i;
			}
			else
			{
				numToRemove = (temp.size() - i) -  1;
				comment = true;
			}
			break;
		}
	}
	// remove stuff after comment
	for (int i = 0; i < numToRemove; i++)
		temp.pop_back();
	
	if(comment)
	{
		int index = temp[temp.size() - 1].find('#');
		// take out everything after #
		temp[temp.size() - 1] = temp[temp.size() - 1].substr(0, index);
	}

	// loop will eventually put a single command
	// in one element in cmd
	// i.g. user puts "ls -a; echo hello"
	// cmd would look like "ls -a" ";" "echo hello"
	while (k < temp.size())
	{
		for ( ;i < temp.size(); i++)
		{
			// if it is a single connector do this
			if((temp[i] == ";") || (temp[i] == "||") || (temp[i] == "&&"))
			{
				if(temp[i] == ";")
					isSemiColon = true;
				else if(temp[i] == "||")
					isLine = true;
				else
					isAmpersand = true;

				k++;
				i++;
				break;
			}
			// this means you if you find ";" or "||" or "&&"
			else if((temp[i].find(";") != string::npos)||
				(temp[i].find("||") != string::npos)||
				(temp[i].find("&&") != string::npos))
			{
				// --------------------------------------
				// TODO: add if statement that parses 
				// something like "ls -a;echo hi"
				// *I would do that ^^^^ in an if statement
				// and put everything(will note as "THIS")
				// into the "else" statement
				// --------------------------------------
				

				// ALLLL THISSSSSSSSSSSSSSSSSSSSS IN THE "ELSE" branch
				// -----------------------------------------------------------
				// if empty and ";" remove the ";" and
				// make a note to push ";" after temp2
				if((temp2.empty()) && (temp[i].find(";") != string::npos))
				{
					temp2 = temp[i];
					if(temp2.size() != 1)
					{
						temp2 = temp2.substr(0, temp2.size() - 1);
					}
					isSemiColon = true;
				}
				// if it's empty and "||" or "&&"; remove them
				// and then push back || or &&
				else if((temp2.empty()) && ((temp[i].find("||") != string::npos) ||
					                        (temp[i].find("&&") != string::npos)))
				{
					temp2 = temp[i];
					if(temp2.size() != 2)
					{
						temp2 = temp2.substr(0, temp2.size() - 1);
						temp2 = temp2.substr(0, temp2.size() - 1);
					}
					// makes a note if it's a || or &&
					if (temp[i].find("||") != string::npos)
					{
						isLine = true;
					}
					else
					{
						isAmpersand = true;
					}
				}
				// if string is not empty
				else if((temp[i].find("||") != string::npos) ||
					    (temp[i].find("&&") != string::npos))
				{
					temp2 = temp2 + " " + temp[i];
					// got to get rid of the "||" or "||"
					temp2 = temp2.substr(0, temp2.size() - 1);
					temp2 = temp2.substr(0, temp2.size() - 1);
					if (temp[i].find("||") != string::npos)
					{
						isLine = true;
					}
					else
					{
						isAmpersand = true;
					}
				}
				else
				{
					temp2 = temp2 + " " + temp[i];
					temp2 = temp2.substr(0, temp2.size() - 1);
					isSemiColon = true;
				}
				k++;
				i++;
				break;
				// ----------------------------------------------------
			}
			else
			{
				// makes sure string doesn't look like " this"
				if(temp2.empty())
				{
					k++;
					temp2 += temp[i];
				}
				// eventually makes a string command "la -a"
				else
				{
					k++;
					temp2 = temp2 + " " + temp[i];
				}
			}
		}
		// adds single command as an element in CMD
		// unless it's a comment xD
		if(!temp2.empty())
			cmd.push_back(temp2);

		if(isSemiColon)
		{
			//cout << "semicolon" << endl;
			cmd.push_back(";");
		}
		else if(isLine)
		{
			//cout << "lines" << endl;
			cmd.push_back("||");
		}
		else if(isAmpersand)
		{
			//cout << "ampersand" << endl;
			cmd.push_back("&&");
		}

		// reset everything
		isSemiColon = false;
		isLine = false;
		isAmpersand = false;
		temp2.clear();
	}

	// using to test to see what is stored in cmd
	//cout << "cmd vector in Parser after parse: " << endl;
	//for (unsigned int i = 0; i < cmd.size(); i++)
	//	cout << cmd.at(i) << endl;

	return;
}

int Parser::execute()
{
	// If I use my imagination hard enough
	// this will magically work
	// every odd number is a connector (besides the last one);
	// 0 and even numbers are the commands
	int status = 0;	
	unsigned int i = 0;
	Executer E;

	// if user puts "ls test ||" or "echo test &&", etc
	// then prompt the user ">" and another command
	if ((cmd.size() != 1) && ((cmd.back() == "||") || (cmd.back() == "&&")))
	{
		string cmd;
		cout << ">";
		getline(cin, cmd);
		setCommand(cmd);
		parse();
	}
	
	// this loop analyzes the connectors
	// and determines what gets runned
	while(i < cmd.size())
	{
		E.setCount(i);						
		this->bPtr = &E;		

		status = bPtr->execute();			
		if(status == -1)
		{
			return status;
		}

		// i + 1 is inbound
		if(((i + 1) < cmd.size()) &&
		   (cmd.size() > 3))						// execute() will have 3 different return value
		{											// -1 if there is an "exit"
			// next connector is ;					// 0 if it ran correctly, or 149 if it failed
			if(cmd.at(i + 1) == ";")				// "it" being execvp 
			{								
				i += 2; 							// i+=2 b/c i++ would give us a connector
			}
			// next connector is &&
			else if(cmd.at(i + 1) == "&&")
			{
				// if previous worked
				if(status == 0)
					i += 2;	 // go to the next command
				else
				{
					// not sure yet
				}
			}
			else if(cmd.at(i + 1) == "||")
			{
				// if previous failed
				if(status == 149)
				{
					i += 2;	// go to the next command
				}
				else
				{
					// not sure yet
				}
			}
		}
		i+=2;
	}	
	return status;
}

void Parser::printCommand()
{
	cout << "Command in Parser: " << command << endl;
}

void Parser::setPtr(Shell_Base* ptr)
{
	bPtr = ptr;
}
