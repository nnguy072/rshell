#include "Shell_Base.h"
#include "Parser.h"
#include "Executer.h"

using namespace std;

int main()
{
	string cmd;
	cout << "$ ";
	getline(cin, cmd);
	//cout << "hi" << endl;
	Executer e;
	//cout << "1" << endl;
	Parser p = Parser(cmd);
	//cout << "2" << endl;
	p.setPtr(&e);
	//cout << "3" << endl;
	p.parse();
	//cout << "4" << endl;
	// testing functions (these work)
	//p.printCmd();
	//p.printCommand();
	//Parser p1;
	//p1.setCommand(cmd);
	//p1.parse();
	//p1.printCmd();
	//p1.printCommand();
	
	Shell_Base* b = &p;
	//cout << "5" << endl;
	b->execute();
	//cout << "6" << endl;

	// testing list of arguments
	// TODO: learn how to fix this error with these things vvv
	//char *args1[] = {"/bin/", (char*) 0};	// this is just "ls" by itself
	//char *args[] = {"/bin/ls", "-a", (char *) 0};	// this is "ls -a"
	


	return 0;
}
