#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
using namespace std;

class Base;
class Connector;
class Command;
class AND;
class OR;
class Scolon;


class Base 
{
    protected:
    	string command;
    public:
    	string getCommand()
    	{
    		return command;
    	}
    	
    	void addcommand (string cmd)
    	{
    		command = cmd;
    	}
    	virtual void clearvec() = 0;
    	virtual bool execution(int input, int output) = 0;
    	virtual void addArg(string temp) = 0;
    	virtual void testfunc(const vector <string> &list, bool &res, 
    		int input, int output) = 0;
};



class Connector: public Base 
{
    protected:
    	Base* leftChild; 
    	Base* rightChild; 
    public:
	    //constructors
	    Connector()
	    {
	    	command = "Cnt";
	    	this->leftChild = NULL;
	    	this->rightChild = NULL;
	    }
	    Connector(Base* left, Base* right)
	    {
	    	command = "Cnt";
	    	this->leftChild = left;
	    	this->rightChild = right;
	    }
	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
	    virtual void clearvec() {}
	    virtual bool execution(int input, int output) = 0;
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res, 
	    	int input, int output) {}
};

class Pipe: public Connector {
	public:
		Pipe(): Connector() {}
	    Pipe(Base* left, Base* right): Connector(left, right) {}

	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
		virtual void clearvec() {}
	    virtual bool execution(int input, int output);
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output) {}
	
};

class Input: public Connector {
	public:
		Input(): Connector() {}
	    Input(Base* left, Base* right): Connector(left, right) {}

	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
	    virtual void clearvec() {}
	    virtual bool execution(int input, int output);
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output) {}
	
};

class Output: public Connector {
	public:
		Output(): Connector() {}
	    Output(Base* left, Base* right): Connector(left, right) {}

	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
	    virtual void clearvec() {}
	    virtual bool execution(int input, int output);
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output) {}
	
};

class DOutput: public Connector {
	public:
		DOutput(): Connector() {}
	    DOutput(Base* left, Base* right): Connector(left, right) {}

	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
	    // ~ANND()
	    // {
	    // 	delete leftChild;
	    // 	delete rightChild;
	    // 	delete this;
	    // }
	    virtual bool execution(int input, int output);
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output) {}
	    virtual void clearvec() {}
	
};



class Command: public Base 
{
    private:
    	vector <string> argList;
    public:
	    //constructors
	    Command() 
	    {
	    	command ="Cmd";
	    }
	    Command(vector<string> cmd)
	    {
	    	command = cmd.at(0);
	    	argList = cmd;
	    }
	    Command(string cmd)
	    {
	    	command = cmd;
	    }
	    
	    virtual void addArg(string temp);
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output);
	    virtual bool execution(int input, int output);
	    virtual void clearvec() {
	    	argList.clear();
	    }

};

class ANND: public Connector {
    public:
	    ANND()
	    {
	    	command = "Cnt";
	    	this->leftChild = NULL;
	    	this->rightChild = NULL;
	    }
	    ANND(Base* left, Base* right)
	    {
	    	command = "Cnt";
	    	this->leftChild = left;
	    	this->rightChild = right;
	    }
	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
	    // ~ANND()
	    // {
	    // 	delete leftChild;
	    // 	delete rightChild;
	    // 	delete this;
	    // }
	    virtual bool execution(int input, int output);
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output) {}
	    virtual void clearvec() {}
};

class Scolon: public Connector {
    public:
	    Scolon()
	    {
	    	command = "Cnt";
	    	this->leftChild = NULL;
	    	this->rightChild = NULL;
	    }
	    Scolon(Base* left, Base* right)
	    {
	    	command = "Cnt";
	    	this->leftChild = left;
	    	this->rightChild = right;
	    }
	    virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
	    virtual bool execution(int input, int output);
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res
	    	, int input, int output) {}
	    virtual void clearvec() {}
};


class ORR: public Connector {
    public:
    	ORR()
	    {
	    	command = "Cnt";
	    	this->leftChild = NULL;
	    	this->rightChild = NULL;
	    }
	    ORR(Base* left, Base* right)
	    {
	    	command = "Cnt";
	    	this->leftChild = left;
	    	this->rightChild = right;
	    }virtual void addLeft(Base* left)
	    {
	    	this->leftChild = left;
	    }
	    virtual void addRight(Base* right)
	    {
	    	this->rightChild = right;
	    }
    	//execute function
    	virtual bool execution(int input, int output);
    	virtual void addArg(string temp) {}
    	virtual void testfunc(const vector <string> &list, bool &res
    		, int input, int output) {}
    	virtual void clearvec() {}
};




#endif
