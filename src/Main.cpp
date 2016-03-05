#include "Shell_Base.h"
#include "Parser.h"
#include "Executer.h"
#include <unistd.h>
using namespace std;

int main()
{
	char hostName[300];
	char loginName[300];
	getlogin_r(loginName, sizeof(loginName));
	gethostname(hostName, sizeof(hostName));
	string cmd;
	int status = 0;

	do
	{
		cout << loginName << "@" << hostName << "$ ";
		getline(cin, cmd);
	}while(cmd.empty() || (cmd.find("#") == 0));

	while(cmd != "exit")
	{
		Executer e;
		Parser p = Parser(cmd);
		p.setPtr(&e);
		p.parse();
		
		Shell_Base* b = &p;
		//status = b->execute();
		b->clear();
		
		if (status == -1)
			return -1;

		cout << loginName << "@" << hostName << "$ ";
		getline(cin, cmd);
	}

	return 0;
}
