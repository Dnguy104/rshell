#!/bin/sh

#to compile
g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
echo "echo \"goodbye\" && exit"
echo "echo \"will we stay on?\" && exit || echo \"yes\""
echo "exit"