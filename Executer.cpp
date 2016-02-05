#include "Executer.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

void Executer::execute()
{
	pid_t pid = fork();
	int status;

	if(pid < 0)
	{
		cout << "Fork failed." << endl;
	}
	if(pid == 0)
	{
		cout << "I am the child" << endl;
	}
	waitpid(-1, &status, 0);

	return;
}
