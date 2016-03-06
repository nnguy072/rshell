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
	vector<string> temp;			// vector that holds original command
	vector<string> test;			// vector that holds things to be tested
	string temp2;					// used to hold individual words that i parsed to push into temp
	//string temp3;					// used for the case "hello;hello" when connector is in the middle
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

//TODO: TESTS
/*
	// checks for tests
	unsigned n = 0;
	for (; i < temp.size(); i++)
	{
		if (temp[i] == "test")
		{
			cout << "test detected." << endl;
			n = i;
			while ((temp[n] != "&&") || (temp[n] != ";") || (temp[n] != "||") || (temp[n] != "\n"))
			{
				cout << "WORKS HERE !" << endl;
				test.push_back(temp[n]);
				cout << "WORKS HERE" << endl;
				n++;
				if (n > temp.size())
					break;
			}
			cout << "finishes this i ugess" << endl;
		}
		// checks for brackets
		if (temp[i] == "[")
		{
			n = i;
			// gets everything until the end of the bracket
			while(temp[n] != "]")
			{
				cout << temp[n] << " is being pushed." << endl;
				test.push_back(temp[n]);
				cout << temp[n] << " has been pushed." << endl;
				n++;
			}
			test.push_back(temp[n]);	// includes the closing "]"
			n++;						// increment so n is position after the closing bracket
		}
	}

	cout << "This is what is in testing" << endl;
	for (unsigned int i = 0; i <test.size(); i++)
		cout << test[i] << endl;
	
	cout << "-------------------------" << endl;


	i = 0;
*/

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
			if((temp[i].find(";") != string::npos)||
				(temp[i].find("||") != string::npos)||
				(temp[i].find("&&") != string::npos))
			{
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
		// unless it's a comment xD
		if(!temp2.empty())
		{
			cmd.push_back(temp2);
		}

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

	//for(unsigned int i = 0; i < cmd.size(); i++)
	//	cout << i << ": " << cmd.at(i) << endl;

	// this loop analyzes the connectors
	// and determines what gets runned
	while(i < cmd.size())
	{
		E.setCount(i);						
		this->bPtr = &E;		

		status = bPtr->execute();			
		if(status == -1)		// if status is -1 then "exit was inputted"
		{						// so we want to exit rshell program
			return status;
		}
		//cout << "hi" << endl;
		// should on on connector now
		// b/c connectors are on odd numbers
		i++;	
		
		//cout << "i:" << i << endl;
		if(i >= cmd.size())
		{
			return status;
		}

		if(cmd.at(i) == ";")
		{
			//cout << "Before i++" << endl;
			i++;
			//cout << "After i++" << endl;
		}
		// if next one is && move to the next one if 
		// previous worked
		else if(cmd.at(i) == "&&")
		{
			// if previous worked
			if(status == 0)
			{
				i++;	 // go to the next command
			}
			else
			{
				i+=3;   // moves on to next connector		
			}
		}
		else if(cmd.at(i) == "||")
		{
			// if previous failed
			if(status == 149)
			{
				i++;	// go to the next command
			}
			else
			{
				i+=3;
			}
		}

		//cout << "i after everything: " << i << endl;
		if(isOdd(i) || i > cmd.size())
		{
			//cout << "goes here" << endl;
			return status;
		}
	}	
	return status;
}

bool Parser::isOdd(unsigned int i)
{
	if((i % 2) == 0)
	{
		return false;
	}	
	else
	{
		return true;
	}
}
void Parser::printCommand()
{
	cout << "Command in Parser: " << command << endl;
}

void Parser::setPtr(Shell_Base* ptr)
{
	bPtr = ptr;
}
