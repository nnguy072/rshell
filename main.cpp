#include <iostream>
#include <vector>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

/* parameters: (argument list in cstring form, simple command w/o arguments)
 * takes in a cstring (argument list) 
 * also takes in a simple command like "ls"/"cd"/"dir"
 * forks and exits that command in the child
 */
void execute(char *a[], string &c)
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

	// lets the child do whatever it wants first
	waitpid(-1, &status, 0);	
	
	return;
}

/* parameters: (*empty* vector<string>, string command)
 * takes in vector<string> by reference
 * and the command then parses it
 * each element of the vector will have a single command e.g. "ls -a"
 */
void parse(vector<string> &v, const string &c)
{
	vector<string> temp;	// this vector.at(i) will hold a single word in the command
	string temp2;			// after parsing this will hold each thing seperated by a connector
	int i = 0;				// 'i' will keep going until it sees a connector, then do something and keep going
	int k = 0;				// 'k' goes through the whole vector temp
	// using the boost library to parse the command
	boost::split(temp, c, boost::is_any_of(" "));

/*
	cout << "==== before parsing =====" << endl;
	for (int i = 0; i < temp.size(); i++)
		cout << temp.at(i) << endl;

	cout << "========================" << endl;
*/

	while (k < temp.size())
	{	
		// loop will go through temp until it sees a connector
		// while it does that it will append each word before connector to a string
		for ( ;i < temp.size(); i++)
		{
			// TODO: make this keep track of connectors; implement || and &&
			// when it sees ";" or "||" or "&&" the loop will end, but then restart starting where 'i' left off
			if(temp[i].find(";") != string::npos)
			{
				// the ";" is always at the end
				// so just remove last element of the string
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
				// for now if it sees "||" or "&&" it will skip over it
				// TODO: implement a way to track || and && for later
				if((temp[i] == "||") || (temp[i] == "&&"))
				{
					k++;
					i++;
					break;
				}
				// this is to make sure it does not look like " this"
				else if(temp2.empty())
				{
					k++;
					temp2 += temp[i];
				}
				// eventually add up to a single command "ls -a"
				else
				{
					k++;
					temp2 = temp2 + " " + temp[i];
				}
			}
		}
		// "v" the vector should be empty
		// every element of the vector should have a single command (temp2)
		v.push_back(temp2);
		temp2.clear();
	}

	// used for testing; showing what's in passed in vector	
	for (int i = 0; i < v.size(); i++)
		cout << v.at(i) << endl;
	
	return;
}

int main()
{
	string cmd;
	int found;
	vector<string> tokens;
	
	// testing list of arguments
	// char *args1[] = {"ls", (char*) 0};	// this is just "ls" by itself
	// char *args[] = {"/bin/ls", "-a", (char *) 0};	// this is "ls -a"

	while (cmd != "exit")
	{
		cout << "$";
		getline(cin, cmd);
		parse(tokens, cmd);
		tokens.clear();
		//execute(args, cmd);
	}
	return 0;
}
