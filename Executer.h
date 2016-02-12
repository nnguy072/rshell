#include "Shell_Base.h"

class Executer: public Shell_Base{
	private:
		// using this to keep track of which process to run
		int count;
		char* convert(const string& s);
	public:
		Executer();
		Executer(int i);
		void execute();
		void setCount(const int& i);
		int getCount();
		char** makeArg(vector<char*>& v, const int &index);
		void vectorDestructor(vector<char*>& v);
};
