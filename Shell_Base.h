#ifndef _SHELL_BASE_H_
#define _SHELL_BASE_H_
#include <vector>
#include <iostream>
using namespace std;

class Shell_Base
{
	protected:
		vector<string> cmd;
		vector<string> arg;
	public:
		virtual void execute() = 0;
		virtual void printCmd() = 0;
		virtual void printArg() = 0;
};

#endif
