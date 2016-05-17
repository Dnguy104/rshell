###Authors
Daniel Nguyen
https://github.com/Dnguy104/
Cole Resetco
https://github.com/Crese002/


#rshell
============

Rshell is a command shell that is designed to emulate the actual BASH terminal. It should be able to output the username and machine name, read in the command line input, parse it, and execute the bash functions correctly.
	Our job is to create a command prompt shell that has 3 different possible 
functions, including “;” , “&&” and “||”. Any semi-colon will cause the next command to occur, any AND operator will execute the following command only if the first one passes, and any OR operator will execute the second command only if the first one fails. The program will also ignore all inputs after a # input.
It will then complete all the commands based on the required results.
Our program will take in raw input and process it into three groups; operators, commands, and arguments. It will also use its built in logic to execute the correct commands with the appropriate flags and data members.

Syntax: `command [argument list] [connector]`


##Instructions on installation and usage

Input the following into your terminal:

```
$ git clone https://github.com/s-vong/rshell.git

$ cd rshell

$ git checkout hw2

$ make

$ bin/rshell
```



##Known bugs
Some Bash-exclusive commands do not work, like cd

Sometimes a random quotaion is outputed and using echo

if connectors are not properly spaced it may not read correctly

single quotations might not be read

a common bug is that the program might not take in the input if it is just one character







##License 
Please read the terms specified in the [LICENSE] file.

[LICENSE]: /LICENSE


##About
This custom shell is made as an assignment for academic reasons.
