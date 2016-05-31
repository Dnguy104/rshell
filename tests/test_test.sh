#!/bin/sh

#to compile
##g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
touch test.txt
test test.txt
test -e test.txt
test -d test.txt
test -f test.txt
[ -f test.txt ]
[ -d test.txt ]
[ -e test.txt ]
