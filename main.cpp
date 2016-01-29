#include <iostream>
#include <vector>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

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

	// pid of parent
	cout << "I am: " << getpid() << endl;
	pid_t pid = fork();
	
	if (pid < 0)	// if pid is negative it's an error
	{
		cout << "Fork failed." << endl;
	}
	if (pid == 0)	// if pid == 0 then it's the child
	{
		cout << "I am the child. " << getpid() << endl;
		int test = execvp("ls", args);
		if (test < 0)
			cout << "Error: exec failed. " << endl;
			return 1;
		exit(0);
	}

	// must be parent usually it's like if pid > 0
	waitpid(-1, &status, 0);	// lets the child do whatever it wants first
	
	cout << "I am the parent." << endl;
	cout << "parent end." << endl;
	return 0;
}
