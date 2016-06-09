#!/bin/sh

#to compile
#g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
touch testy.txt
touch testyy.txt
ls | cat
ls -al | more

rm testy.txt
rm testyy.txt
exit
