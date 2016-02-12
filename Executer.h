#include "Shell_Base.h"

class Executer: public Shell_Base{
	private:
	
	public:
		void execute();
		void printCmd();
		void printArg();
		char* convert(const string& s);
<<<<<<< HEAD
		void makeArgs();
=======
		void vectorDestructor(vector<char*> v);
>>>>>>> 8e15b837fd540b0ffb2b1f5795da2757c49d67a5
};
