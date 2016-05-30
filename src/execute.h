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
    	virtual bool execution() = 0;
    	virtual void addArg(string temp) = 0;
    	virtual void testfunc(const vector <string> &list, bool &res) = 0;
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
	    	this->leftChild = NULL;
	    	this->rightChild = NULL;
	    }
	    Connector(Base* left, Base* right)
	    {
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

	    virtual bool execution() = 0;
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res) {}
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
	    virtual void testfunc(const vector <string> &list, bool &res);
	    virtual bool execution();

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
	    virtual bool execution();
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res) {}
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
	    virtual bool execution();
	    virtual void addArg(string temp) {}
	    virtual void testfunc(const vector <string> &list, bool &res) {}
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
    	virtual bool execution();
    	virtual void addArg(string temp) {}
    	virtual void testfunc(const vector <string> &list, bool &res) {}
};




#endif
