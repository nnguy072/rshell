FLAGS = -Wall -Werror -ansi -pedantic

main: Main.cpp Executer.o Parser.o Shell_Base.o
	g++ $(FLAGS) Main.cpp Executer.o Parser.o Shell_Base.o

Shell_Base.o: Shell_Base.cpp Shell_Base.h
	g++ $(FLAGS) -c Shell_Base.cpp Shell_Base.h

Parser.o: Parser.cpp Parser.h
	g++ $(FLAGS) -c Parser.cpp Parser.h

Executer.o: Executer.cpp Executer.h
	g++ $(FLAGS) -c Executer.cpp Executer.h

clean:
	rm a.out *.o *.gch
