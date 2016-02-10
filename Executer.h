#include "Shell_Base.h"

class Executer: public Shell_Base{
	private:
				
	public:
		void execute();
		void printCmd();
		void printArg();
		char* convert(const string& s);
};
