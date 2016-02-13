#ifndef _SHELL_BASE_H_
#define _SHELL_BASE_H_
#include <vector>
#include <iostream>
using namespace std;

class Shell_Base
{
	protected:
		static vector<string> cmd;
	public:
		void clear();
		virtual int execute() = 0;
};

#endif
