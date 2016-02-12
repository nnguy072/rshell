#include "Parser.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <string.h>
using namespace std;

Parser::~Parser()
{
	// nothing
}

void Parser::setCommand(string &c)
{
	command = c;
}

char* Parser::convert(const string &s)
{
	char *c = new char[s.size() +1];
	strcpy(c, s.c_str());
	return c;
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
		// TODO: convert string -> c_string then push into vector
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
	cout << "cmd vector in Parser after parse: " << endl;
	
	for (unsigned int i = 0; i < cmd.size(); i++)
		cout << cmd.at(i) << endl;

	return;
}

void Parser::execute()
{
	bPtr->execute();
}

void Parser::printCommand()
{
	cout << "Command in Parser: " << command << endl;
}

void Parser::printCmd()
{
	cout << "Cmd in Parser: " << endl;
	for (unsigned int i = 0; i < cmd.size(); i++)
		cout << cmd.at(i) << endl;
}

void Parser::printArg()
{
	cout << "Arg in Parser: " << endl;
	//for (unsigned int i = 0; i < arg.size(); i++)
	//	cout << arg.at(i) << endl;
}

void Parser::setPtr(Shell_Base* ptr)
{
	bPtr = ptr;
}
