#include <iostream>
#include <vector>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void execute(char *a[], string c)
{
	pid_t pid = fork();
	int status;

	if (pid < 0)	// if pid is negative it's an error
	{
		cout << "Fork failed." << endl;
	}
	if (pid == 0)	// if pid == 0 then it's the child
	{
		//cout << "I am the child. " << getpid() << endl;
		execvp(c.c_str(), a);
		exit(0);
	}

	// must be parent usually it's like if pid > 0
	waitpid(-1, &status, 0);	// lets the child do whatever it wants first
	
	//cout << "I am the parent." << endl;
	//cout << "parent end." << endl;i
	return;
}


int main()
{
	string cmd;
	int found;
	vector<string> tokens;
	int status;
	
	// this for parsing
	//string str = "hello I am testing something";
	//boost::split(tokens, str, boost::is_any_of(" "));

	// testing list of arguments
	char *args1[] = {"ls", (char*) 0};	// this is just "ls" by itself
	char *args[] = {"/bin/ls", "-a", (char *) 0};	// this is "ls -a"

	while (cmd != "exit")
	{
		cout << "$";
		cin >> cmd;
		execute(args, cmd);
	}
	return 0;
}
