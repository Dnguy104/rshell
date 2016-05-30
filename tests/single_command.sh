#!/bin/sh

#to compile
g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
echo "echo \"I hope this works\""
echo "ls - a"
echo "mkdir" 
echo "mkdir --help" 
echo "ls"
