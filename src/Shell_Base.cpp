#ifndef SHELL_BASE
#define SHELL_BASE
#include "Shell_Base.h"

vector<string> Shell_Base::cmd;

void Shell_Base::clear()
{
	//because cmd is a vector of strings clear is sufficient
	cmd.clear();
}


#endif

