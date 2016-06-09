#!/bin/sh

#to compile
#g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
touch testy.txt
touch testyy.txt
echo "(true)" > testy.txt
cat < testy.txt > testyy.txt
cat < testy.txt >> testyy.txt
cat testyy.txt
ls > testyy.txt

rm testy.txt
rm testyy.txt
exit
