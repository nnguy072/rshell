#include "Shell_Base.h"
#include <iostream>
using namespace std;

class Parser: public Shell_Base{
	private:
		string command;
		Shell_Base* bPtr;
	public:
		Parser(): command("") {};
		~Parser();
		Parser(string &c){command = c;};
		void setCommand(string &c);
		void setPtr(Shell_Base* ptr);
		void parse();
		int execute();
		void printCommand();
		void setCount(const int& i);
};
