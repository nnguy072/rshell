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
	unsigned int i = 0;
	unsigned int k = 0;

	// parse command using boost library
	boost::split(temp, command, boost::is_any_of(" "));
	while (k < temp.size())
	{
		// goes through loop until it sees a connector
		// append each word before conector into a string
		for ( ;i < temp.size(); i++)
		{
			// ";" always connected to end "ls -a;"
			// so for not just remove
			// TODO: make it do something if it sees ";"
			if(temp[i].find(";") != string::npos)
			{
				if(temp2.empty())
				{
					temp2 = temp[i];
					temp2 = temp2.substr(0, temp2.size() - 1);
				}
				else
				{
					temp2 = temp2 + " " + temp[i];
					temp2 = temp2.substr(0, temp2.size() - 1);
				}
				k++;
				i++;
				break;
			}
			else
			{
				// if it sees || or && it just skips for now
				// TODO: make it do something it sees stuff
				if((temp[i] == "||") || (temp[i] == "&&"))
				{
					k++;
					i++;
					break;
				}
				// makes sure string doesn't look like " this"
				else if(temp2.empty())
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
		// clears to reset
		temp2.clear();
	}
//	cmd.push_back(NULL);

	// using to test to see what is stored in cmd
	//for (unsigned int i = 0; i < cmd.size() - 1; i++)
	//	cout << cmd[i] << endl;

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
