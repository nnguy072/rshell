COMMAND RSHELL
===

AUTHORS
---
Rodney Ho

Nam Nguyen

CONTENTS
---
This program mimics the behavior of a command shell prompt. It has the ability to execute any commands located in /bin,
/usr/bin such as ls and echo. However, commands that are native to bash such as cd, will not work in this program. Single
commands, multiple commands, and comments all work. The syntax for single commands are the same for bash. Simply ls,
echo hello, or mkdir "filename" is sufficient. Multiple commands work with 3 avaliable connectors. The ";", "&&", and 
"||". The semi-colon connector works with no white space such as "ls -a; echo hello", while the ampersand and vertical
bar are used with space such as "ls -a && echo hello" or "ls -a || echo hello". The ";" states that the next command will 
always be executed regardless of the success of the previous. The "&&" states that the next command will be executed only 
if the first command is successful. The "||" command states the next command will execute only if the first one failed.
	Comments can also be added, but will not appear in the terminal. For example, "ls #list" adds the comment "list" but the
	comment itself is invisible when executed. Comments can also be multiply lines and consisting of white space. To quit 
	the program, simply type "exit". Exit can be used as a single command or a multiple command.

LIST OF KNOWN BUGS
---
* Connectors need to follow conventional rules
* ls -a;echo "hello" will not parase correctly; however, ls -a; echo "hello" does not work
* Not all commands in bash have been tested
* Commands that are built-in to bash will not work (e.g. cd)
* ls is not color coded (All types of items in the directory are the same color)
* Precedence does not work; however a test has been written for it
* Test/[] sometimes does not work correctly(prints out false even if true)
* When using Test/[] the semi colon ";" can't be next to the command
* EX: test -e /path/name ; NOT test -e /path/name;

LANGUAGE USED
---
* C++

READ LICENSE
