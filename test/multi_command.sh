#!/bin/sh

#to compile
g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
echo "ls && ls -a" 
echo "mkdir || echo \"That didnt work\" && echo \"done\"" 
echo "echo \"checking contents of ls and ls -a\" && ls && ls -a"
echo "echo\"I\"; echo \"really\"; echo \"Hope\"; echo \"this\"; echo \"works\"; 