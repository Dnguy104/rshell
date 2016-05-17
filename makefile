COMPLIES = g++
FLAGS = -Wall -Werror -ansi -pedantic


all:
	 mkdir -p ./bin
	 $(COMPLIES) $(FLAGS) ./src/main.cpp ./src/execute.cpp -o ./bin/rshell

execute:
	  $(COMPLIES) $(FLAGS) ./src/execute.cpp

clean:
	  rm -rf ./bin	

