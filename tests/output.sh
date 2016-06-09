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
echo "testing output" > testyy.txt
echo "testing output" >> testyy.txt
cat < testyy.txt >> testy.txt


rm testy.txt
rm testyy.txt
exit
