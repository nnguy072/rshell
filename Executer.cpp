#include "Executer.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;


void Executer::execute()
{	
	vector<char*> test = cmd;
	
	cout << "displaying stuff in test: " << endl;
	for(unsigned int i = 0; i < test.size() - 1; i++)
		cout << i << " " << test.at(i) << endl;

	char** arg = &cmd[0];

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
	waitpid(-1, &status, 0);

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
