#include "Executer.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

void Executer::execute()
{
	//char* a[4] = {(char *)"ls", (char *)"-m", (char *)"-a", (char *) 0};
	
	int status;
	pid_t pid = fork();

	if(pid < 0)
	{
		cout << "Fork failed." << endl;
	}
	if(pid == 0)
	{
		cout << "I am the child" << endl;
		//execvp("ls", a);
	}
	waitpid(-1, &status, 0);

	return;
}

void Executer::printArg()
{
	cout << "Exeuter::printArg(): ";
	for(unsigned int i = 0; i < arg.size(); i++)
		cout << arg.at(i) << endl;
}

void Executer::printCmd()
{
	cout << "Executer::printCmd: ";
	for(unsigned int i = 0; i < cmd.size(); i++)
		cout << cmd.at(i) << endl;
}
