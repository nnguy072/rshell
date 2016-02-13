FLAGS = -Wall -Werror -ansi -pedantic

all: rshell 

rshell:
	([ ! -d bin ] && mkdir bin) || [ -d bin ]
	g++ $(FLAGS) src/Main.cpp src/Parser.cpp src/Executer.cpp src/Shell_Base.cpp -o bin/rshell
