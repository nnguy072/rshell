#include "Shell_Base.h"
#include "Parser.h"
#include "Executer.h"

using namespace std;

int main()
{
	string cmd;
	cout << "$";
	getline(cin, cmd);
	
	// testing Parser functions
	Parser p = Parser(cmd);
	p.parse();
	p.printCmd();
	p.printCommand();
	
	// testing list of arguments
	// TODO: learn how to fix this error with these things vvv
	//char *args1[] = {"/bin/", (char*) 0};	// this is just "ls" by itself
	//char *args[] = {"/bin/ls", "-a", (char *) 0};	// this is "ls -a"
	
	return 0;
}
