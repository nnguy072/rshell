#include "Shell_Base.h"
#include "Parser.h"
#include "Executer.h"

using namespace std;

int main()
{
	string cmd;
	cout << "$ ";
	getline(cin, cmd);

	while(cmd != "exit")
	{
		Executer e;
		Parser p = Parser(cmd);
		p.setPtr(&e);
		p.parse();
		
		Shell_Base* b = &p;
		b->execute();
		b->clear();

		cout << "$ ";
		getline(cin, cmd);
	}

	// testing list of arguments
	// TODO: learn how to fix this error with these things vvv
	//char *args1[] = {"/bin/", (char*) 0};	// this is just "ls" by itself
	//char *args[] = {"/bin/ls", "-a", (char *) 0};	// this is "ls -a"

	// TODO: fix exit bug where when an incorrect command causes exit not to work properly afterwards.
	
	// EX: "l" is not a command, type in string exit and does nothing.  SUPPOSE to exit.  After typing
	// string exit the second time shell exits.
	// I'm speculating it has to do with how waitpid works.
	
	// EX2: "l" is not a command, type in ls and ls not a working directory. SUPPOSE to list. After
	// typing string ls the second time the shell lists
	
	// Ex3: "l" is not a command, type in ls -a and it works. EXPECTED the need to type it again in order
	// for it to take effect.
	
	//Also notice if you try too much fork will fail and execvp will fail with EX2.  And notice that
	//the message "ls cannot access __".  The underscore changes letters depending on previous input
	//For instance it can be ls cannot access a or ls cannot access ls or some random.

	//echo can't echo out more than one word
	
	//specs require to use perror and a directory called tests taht should contain bash scripts that test
	//cases


	//ADDED: added a exit functionality but cannot complete with unknown error checking bugs and connector.
	//Added proper destructor in Execute.cpp
	//Added proper destructor in Shell_Base.cpp and was called in main as after b->execute


	return 0;
}
