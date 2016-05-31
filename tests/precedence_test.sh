#!/bin/sh

#to compile
#g++ -Wall -Werror -ansi -pedantic main.cpp execute.cpp

#tests
(echo bb) && (echo a && echo a)
(echo aa && (echo a && (echo bb))) && (echo aa)
(echo bb) && (echo a && (echo aa))
(echo bb) && (echo a || echoo aa)
(echo bb) && (echoo a || echo aa)
