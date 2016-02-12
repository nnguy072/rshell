#include "Executer.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <boost/algorithm/string.hpp>
using namespace std;

char* Executer::convert(const string &s)
{
	char* c = new char[s.size() + 1];
	strcpy(c, s.c_str());
	return c;
}

	
void Executer::vectorDestructor(vector<char*> v)
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		//deletes char* in each element of the vector
		delete []v.at(i);
	}
	//to make sure objects are destructed and makes vector size 0
	v.clear();
}

void Executer::execute()
{	
	vector<char*> vCStr;
	string tempStr = cmd.at(0);
	string tempStr2 = "";
	vector<string> tempV;
	unsigned int k = 0;
	//int counter = 1;

	boost::split(tempV, tempStr, boost::is_any_of(" "));
	while(k < tempV.size())
	{
		for(unsigned int i = 0; i < tempV.size(); i++)
		{
			if(tempV.at(i).find(";") != string::npos)
			{
				if(tempStr2.empty())
				{
					tempStr2 = tempV.at(i);
					tempStr2 = tempStr2.substr(0, tempStr2.size() - 1);
				}
				else
				{
					tempStr2 = tempStr2 + " " + tempV.at(i);
					tempStr2 = tempStr2.substr(0, tempStr2.size() - 1);
				}
				i++;
				k++;
				break;
			}
			else if((tempV.at(i) == "||") || (tempV.at(i) == "&&"))
			{
				i++;
				k++;
				break;
			}
			else if(tempStr2.empty())
			{
				k++;
				tempStr2 += tempV.at(i);
			}
			else
			{
				k++;
				tempStr2 = tempStr2 + " " + tempV.at(i);
			}
		}
	}
	for(unsigned int i = 0; i < tempV.size(); i++)
	{
		vCStr.push_back(convert(tempV.at(i).c_str()));
	}
	char** arg = &vCStr.at(0);

	int status;
	pid_t pid = fork();

	if(pid < 0)
	{
		cout << "Fork failed." << endl;
	}
	if(pid == 0)
	{
//		cout << "I am the child" << endl;
		if (execvp(arg[0], arg) < 0)
		{
			cout << "execvp failed." << endl;
		}
	}
	vectorDestructor(vCStr);
	waitpid(-1, &status, 0);
	//vectorDestructor(vCStr); doesnt seem to make a difference to the exit bug if before/after waitpid

	return;
}

void Executer::printArg()
{
	cout << "Exeuter::printArg(): ";
	//for(unsigned int i = 0; i < arg.size(); i++)
	//	cout << arg[i] << endl;
}

void Executer::printCmd()
{
	cout << "Executer::printCmd: ";
	for(unsigned int i = 0; i < cmd.size(); i++)
		cout << cmd.at(i) << endl;
}
