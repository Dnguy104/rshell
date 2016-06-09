#include <iostream>
#include <string>

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

#include "execute.h"


void Command::addArg(string temp)
{
	this->argList.push_back(temp);
	return;
}

void Command::testfunc(const vector <string> &list, bool &res
	, int input, int output)
{
	if(dup2(output,1) < 0) 
    {
        perror("dup2");
        res = false;
        return;
    }
	if(dup2(input,0) < 0 ) 
	{
    	perror("dup2");
        res = false;
        return;
    }
	
	
	struct stat temp;
	string flag;
	string pathF;
	
	if (list.size() == 2) // tests whether the length of the 
	{						// command is correct
		flag = "-e";
		pathF = list.at(1);
	}
	else if ( list.size() == 3)
	{
		flag = list.at(1);
		pathF = list.at(2);
	}
	else
	{
		res = false;
		return;
	}
	
	if (stat(pathF.c_str(),&temp) == 0) // tests whether file exists
	{
		res = true;
	}
	else
	{
		res = false; // does not exist
		cout << "(false)" << endl;
		//perror("stat");
		return;
	}
	
	
	if (flag == "-e") 
	{
		cout << "(true)" << endl;
        res = true;
        return;
	}
	else if (flag == "-f") 
	{								// tests if it is a regular file
        if (S_ISREG(temp.st_mode)) 
        {
            cout << "(true)" << endl;
            res = true;
            return;
            
        }
        else 
        {					
            cout << "(false)" << endl;
            res = false;
            return;
        }
    }
    else if (flag == "-d") 
	{								// tests if it is a directory
        if (S_ISDIR(temp.st_mode)) 
        {
            cout << "(true)" << endl;
            res = true;
            return;
        }
        else 
        {
            cout << "(false)" << endl;
            res = false;
            return;
        }
    }
	else 				// if the flag is invalid, it will ouput error
	{
        cout << "Error:" << flag << " is not a valid flag."  << endl;
        res = false;
        return;
    }  

}




bool Command::execution(int input, int output)
{
    bool result = true; // this is the return bool
    int tempdup1 = 0;
    int tempdup2 = 0;
    //cout << "Starting exicution" << endl;
    
    if (argList[0] == "test")
    {
    	testfunc(argList, result, input, output);
    	return result;
    }
    
    // for (unsigned int i = 0; i < argList.size(); i++)
    // {
    // 	cout << argList.at(i) << " ";
    // }
    // cout << endl;
    
	char** newArg = new char* [this->argList.size() + 1];

	if(this->command == "exit")
	{
		exit(0);
	}

    //cout << "Passed exit check" << endl;
    
	for(unsigned i = 0; i < this->argList.size(); ++i)
	{
		newArg[i] = new char[argList.at(i).size() + 1];
		std::strcpy(newArg[i], argList[i].c_str());
	}
	
	//cout << "Passed Strcpy" << endl;
	
	newArg[this->argList.size()] = NULL;

	// for(unsigned i = 0; i < this->argList.size(); ++i)
	// {
	//     printf("%s\n", newArg[i]);
	// }

	// cout << this->command << endl;

	
	//cout << "Passed bool result = true" << endl;
	
	pid_t pid = fork(); 

	if ( pid < 0)
	{
		perror("Fork");
		exit(-1);
	}
	else if (pid >= 0)
	{
		if (pid == 0) //child process
		{
			
			tempdup1 = dup2(output,1);
			tempdup2 = dup2(input,0);
			
			
			if(tempdup1 < 0) 
		    {
		        perror("dup2");
		        result = false;
		        return result;
		    }
			if(tempdup2 < 0 ) 
			{
		    	perror("dup2");
		        result = false;
		        return result;
		    }
			
			
			if(execvp(newArg[0], newArg) == -1)
			{
				result = false;
				perror("execvp");
				exit(1);
			}	
			// printf("child: %d\n", pid);

		}
		else if (pid > 0) //parent process
		{
			int status;
			if(waitpid(pid, &status, 0) < 0) 
			{
	        	perror("wait");
	    	}
	            
	        if ( WEXITSTATUS(status) > 0 || WEXITSTATUS(status) < 0 ) 
	        {
	            result = false;
	        }

			// printf("parent: %d\n", pid);
		}
	}

    //cout << "Deleting arg" << endl;

	for(unsigned i = 0; i < this->argList.size(); ++i)
	{
		delete[] newArg[i];
	}

	delete[] newArg;

	// if (result == true)
	// {
	// 	cout << "true\n";
	// }
	// else
	// {
	// 	cout << "false\n";
	// }

	return result;
}

bool Input::execution(int input, int output)
{
	string inputfile = rightChild->getCommand();
	int temp = open(inputfile.c_str(),O_RDONLY);
	
	return leftChild->execution(temp, output);
	
	
}

bool Output::execution(int input, int output)
{
	string outputfile = rightChild->getCommand();
	//mode_t mode2 = S_IRGRP | S_IWUSR | S_IRUSR | S_IWGRP;
	mode_t mode2 = S_IRWXU | S_IRWXG;
	mode_t mode1 = O_TRUNC | O_WRONLY| O_CREAT;
	int temp = open(outputfile.c_str(), mode1, mode2);
	
	return leftChild->execution(input, temp);
	
	
}

bool DOutput::execution(int input, int output)
{
	string outputfile = rightChild->getCommand();
	//mode_t mode2 = S_IRGRP | S_IWUSR | S_IRUSR | S_IWGRP;
	mode_t mode2 = S_IRWXU | S_IRWXG;
	mode_t mode1 = O_APPEND | O_WRONLY| O_CREAT;
	int temp = open(outputfile.c_str(), mode1, mode2);
	
	return leftChild->execution(input, temp);
	
	
}
		
bool Pipe::execution(int input, int output)
{
	int filedescrip[2];

    if(pipe(filedescrip) < 0) 
    {
        perror("pipe");
        return false;
    }


    if(leftChild->execution(input,filedescrip[1])) 
    {
    	close(filedescrip[1]);
    	
    	if(rightChild->execution(filedescrip[0],output))
    	{
    		close(filedescrip[0]);
    		return true;
    	}	
    	else
    	{
    		close(filedescrip[0]);
    		return false;
    	}
    }
    else
    {
    	close(filedescrip[1]);
    	return false;
    }

	
	
}
		
		
bool ANND::execution(int input, int output) 
{
	//cout << "and" << endl;
	if ( this->leftChild->execution(input, output) == true)
	{
	   if(this->rightChild->execution(input, output) == true)
	   {
		   //cout << "true" << endl;
		   return true;
	   }
	   else 
	   {
		   //cout << "false" << endl;
		   return false;
	   }
	}
	else 
	{
		//cout << "false" << endl;
		return false;
	 }
}

bool ORR::execution(int input, int output) 
{
	//cout << "or" << endl;
	if ( this->leftChild->execution(input, output) == true)
	{
		//cout << "true" << endl;
		return true;
	}
	else 
	{
		if(this->rightChild->execution(input, output) == true)
		{
			//cout << "true" << endl;
			return true;
		}
		else 
		{
			//cout << "false" << endl;
			return false;
		}
	}
}

bool Scolon::execution(int input, int output) 
{
	//cout << " scollon" << endl;
	this->leftChild->execution(input, output);
	
	if (this->rightChild != NULL)
	{
		if (this->rightChild->execution(input, output) == true)
		{
			//cout << "true" << endl;
			return true;
		}
		else 
		{
			//cout << "false" << endl;
			return false;
		}
	}
	else
	{
		//cout << "true" << endl;
		return true;
	}
}



// int main()
// {
// 	Command temp("echo");
// 	temp.addArg("echo");
// 	temp.addArg("111");
	
// 	Command temp1("echo");
// 	temp1.addArg("echoo");
// 	temp1.addArg("222");
	
// 	Base* temp = new Command temp(vector);

	
// 	Command temp2("echo");
// 	temp2.addArg("echo");
// 	temp2.addArg("333");

// 	// temp.execution();
// 	// temp1.execution();
// 	// temp2.execution();

// 	Base* tempp = &temp;
// 	Base* tempp1 = &temp1;
// 	Base* tempp2 = &temp2;

// 	ANND temppp(tempp, tempp1);
// 	Base* tempppp = &temppp;
// 	ANND temppp1(&temppp, &temp2);

// 	ANND temppp(tempp, tempp1);
// 	Base* tempppp = &temppp;
// 	ANND temppp1(tempppp, &temp2);
	
// 	temppp1.execution();
	
// 	return 0;
// }


