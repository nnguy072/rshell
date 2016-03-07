#include "Shell_Base.h"

class Executer: public Shell_Base{
	private:
		// using this to keep track of which process to run
		int count;
		int testCount;
		char* convert(const string& s);
	public:
		Executer();
		Executer(int i);
		int execute();
		void setCount(const int& i);
		void setTestCount(const int& i);
		int getCount();
		int getTestCount();
		char** makeArg(vector<char*>& v, const int &index);
		void vectorDestructor(vector<char*>& v);
};
