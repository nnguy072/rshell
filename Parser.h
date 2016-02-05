#include "Shell_Base.h"
#include <vector>
#include <iostream>
using namespace std;

class Parser: public Shell_Base{
	private:
		string command;
		//vector<string> cmd;
		//vector<string> arg;
	public:
		Parser(): command("") {};
		~Parser();
		Parser(string &c){command = c;};
		void parse();
		void order();
		void execute();
		void printCommand();
		void printCmd();
		void printArg();
};
