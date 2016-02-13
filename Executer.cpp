#include "Executer.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <boost/algorithm/string.hpp>
#include <cstdio>
using namespace std;


Executer::Executer()
{
	// does nothing
}

Executer::Executer(int i)
{
	count = i;
}

void Executer::setCount(const int& i)
{
	count = i;
}

int Executer::getCount()
{
	return count;
}

char* Executer::convert(const string &s)
{
	char* c = new char[s.size() + 1];
	strcpy(c, s.c_str());
	return c;
}

void Executer::vectorDestructor(vector<char*>& v)
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		//deletes char* in each element of the vector
		delete []v.at(i);
	}
	//to make sure objects are destructed and makes vector size 0
	v.clear();
}

char** Executer::makeArg(vector<char*>& v,const int &index)
{
	string tempStr = cmd.at(index);
	string tempStr2;
	vector<string> tempV;

	// using boost library we split tempStr(holds a single command i.g. cmd.at(0))
	// seperates something like "ls -a -l" into "ls" "-a" "-l" and puts it into a vec
	boost::split(tempV, tempStr, boost::is_any_of(" "));

	// since echo sometimes has a sentence as a second argument
	// we need to do something different
	if (tempV.at(0) == "echo")
	{
		// pushes back first element "echo"
		v.push_back(convert(tempV.at(0).c_str()));
		// for all the arguments put them together into a big string
		// then use that as a second "argument" for echo
		for (unsigned int i = 1; i < tempV.size(); i++)
		{
			if (tempStr2.empty())
			{
				tempStr2 = tempV.at(i);
			}
			else
			{
				tempStr2 = tempStr2 + " " + tempV.at(i);
			}
		}
		v.push_back(convert(tempStr2.c_str()));
	}
	else
	{
		// for each element convert from string -> const char* -> char*
		// store into vCStr
		for(unsigned int i = 0; i < tempV.size(); i++)
		{
			v.push_back(convert(tempV.at(i).c_str()));
		}
	}
	// ADD NULL at the end needed for execvp
	v.push_back(NULL);

	// takes pointer to vector
	// and assigns it char* array pointer
	// in what i think is converting from vector to array
	// w/o having to copy each element
	char** arg = &v.at(0);
	
	return arg;
}

// executes 1 single function
// return value: returns 0 if execvp was succesful
//               or 149 if it failed
//               or -1 if "exit" was entered 
int Executer::execute()
{
	vector<char*> vCStr;
	// if the next command is "exit" then return -1
	if (cmd.at(getCount()).find("exit") != string::npos)
	{
		return -1;
	}
	char** arg = makeArg(vCStr, getCount());
	int status;
	// makes a child function
	pid_t pid = fork();
	
	// if pid is negative something went wrong
	if(pid < 0)
	{
		perror("Fork failed");
	}
	// pid == 0 is the child
	if(pid == 0)
	{
		// does whatever child needs to do
		//cout << "I am the child" << endl;
		// execvp will return -1 if execvp failed to execute
		if (execvp(arg[0], arg) < 0)
		{
			// same error as the normal terminal
			// "-bash: <command>: command not found"
			cout << "-bash: " << arg[0] << ": command not found" << endl;
			_exit(149); // if execvp fails to work, return vale is 149
		}
		_exit(0);	// stops child process w/ return value of 0
	}
	vectorDestructor(vCStr);
	// waitpid lets the child process do it's thing
	// before the parent continues again
	waitpid(-1, &status, 0);
	int childReturnValue = WEXITSTATUS(status);
	
	return childReturnValue;
}
