#!/bin/sh

#Compile main.cpp\execute
g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#Commands (single)
echo "echo \"I hope this works\"" #return: I hope this works
echo "ls - a" #return: . execute.cpp execute.h .. a.out
echo "mkdir" #return: mkdir: missing operand Try 'mkdir --help' for more info
echo "mkdir --help" #Returns the help page

#Commands (multi)
echo "ls && ls -a" #returns both directory contents
echo "mkdir || echo \"That didnt work\" && echo \"done\"" #return "That didnt
# work" "done"
echo "echo \"checking contents of ls and ls -a\" && ls && ls -a"
#returns: Checking contents of ls and ls -a, followed by the contents

