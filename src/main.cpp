#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>
#include "execute.h"

using namespace std;

// test command to parse
//
// ls -a; echo "hello world" || echo "Goodbye world"


vector <string> createarguments(string Fullstr, unsigned &check)
//takes in idividual commands and formats them into a vector of strings
//that can be read by the execution command
{
	//cout << "starting string creation" << endl;
    //example cstr = echo "Hello all"
    vector <string> Final;
    unsigned start = 0;
    unsigned end = 0;
   
    
    while (end < Fullstr.size())
    {
    	if (Fullstr == ";" || Fullstr == "||" || Fullstr == "&&")
    	{
    		Final.push_back(Fullstr);
    		//cout << "Found single operator: " << Fullstr << endl;
    		return Final;
    	}
    	if (Fullstr.at(end) =='#' )
    	{
    		//Final.push_back(Fullstr.substr(start, (end -  start)));
    		//cout << "Testing vector of strings" << endl;
			for(unsigned i = 0; i < Final.size(); i++)
    		{
    			//cout <<"_"<< Final.at(i) << "_" << endl;
    		}
    		check = 1;
    		//cout << "Check marked" << endl;
    		return Final;
    	}
    	if (Fullstr.at(end) == ' ')
    	{
    		
    		Final.push_back(Fullstr.substr(start, (end - start)));
    		start = end;
    		if(end < Fullstr.size() - 1)
    		{
    			start++;
    			end++;
    		}
    		
    	}
    	if (Fullstr.at(end) == '\"' )
    	{
    		start = end;
    		while (Fullstr.at(start) == '\"')
    		{
    			start++;
    		}
    		end++;
    		while(Fullstr.at(end) != '\"')
    		{
    			end++;
    		}
    		Final.push_back(Fullstr.substr(start, (end - start)));
    		start = end;
    	}
    	if ((end == Fullstr.size() - 1) &&(start != end))
    	{
    		Final.push_back(Fullstr.substr(start, (end - start + 1)));
    	}
    	if (Fullstr.at(end) =='#' )
    	{
    		if(Fullstr.substr(start, (end - start)) != " ")
    		{
    		Final.push_back(Fullstr.substr(start, (end -  start)));
    		}
    		//cout << "Testing vector of strings" << endl;
			for(unsigned k = 0; k < Final.size(); k++)
    		{
    			//cout << "_" << Final.at(k) << "_" << endl;
    		}
    		check = 1;
    		//cout << "Check marked" << endl;
    		return Final;
    	}
    	end++;
    }
    //cout << "Testing vector of strings" << endl;
    for(unsigned i = 0; i < Final.size(); i++)
    {
    	//cout <<  "_" <<Final.at(i) << "_" <<  endl;
    }
    
    return Final;
    
}


void breakstring(string Test, Base* Op) // Breaks the full string up
// into smaller strings, which are designated as command or operator;
//commands are then sent though the "Createarguments" fuction to be
// broken up into a vector of strings. The function then builds a tree
//and then executes the tree.
{
	unsigned check = 0;
	unsigned firstcheck = 0;
	unsigned lastend = 0;
	unsigned currpos = 0;
	 unsigned sao = 0;
	 
	string str1;
	string str2;
	string str3;
	vector <string> tempvec;
	//vector <char*> argument list; 
	if (Test == "" || Test == " ")
	{
		return;
	}
	while((currpos != Test.size()) && (firstcheck == 0 ))
		{
	
	if (Test.at(currpos) == ';')
				{
					str1 = Test.substr(lastend, (currpos - lastend));
					tempvec = createarguments(str1,check);
					Base* Tree = new Command(tempvec);
					//Tree->addArg("\0");
					if(check == 1)
					{
						Op = new Scolon(Tree, NULL);
						Op->execution();
						return;
					}
					tempvec.clear();
					lastend = currpos;
					str2 = Test.substr(lastend, (currpos - lastend + 1));
					tempvec = createarguments(str2,check);
					tempvec.clear();
					if(currpos + 1 == Test.size())
					{
				//cout << "This is the first command (string1)" << str1 << endl;
				//cout << "This is the first operator (string2)" <<str2 << endl;
						Op->execution();
						return;
					}
					currpos++;
						while((Test.at(currpos) != '|' && Test.at(currpos) 
						!= ';' && Test.at(currpos) != '&'))
							{
								currpos++;
		//						cout << "currpos in ;: " 
		//<< currpos << "and what is at: " << Test.at(currpos) << endl;
                                 if(currpos == Test.size() - 1)
                                {
                                	lastend++;
                                	if(Test.at(lastend) == ' ')
                                	{
                                		lastend++;
                                	}
                                	str3 = Test.substr(lastend,
                                	(currpos - lastend + 1));
                                	tempvec = createarguments(str3,check);
                                	Base* Tree2 = new Command(tempvec);
                                	//Tree2->addArg("\0");
                                	Op = new Scolon(Tree, Tree2);
                                	Tree = 0;
                                	Tree2 = 0;
                                	
                                	if(check == 1)
									{
										Op->execution();
										return;
									}
									tempvec.clear();
                //cout << "This is the first command (string1)" << str1 << endl;
				//cout << "This is the first operator (string2)" <<str2 << endl;
				//cout << "This is the second command (string3)" <<str3 << endl;
									Op->execution();
                                    return;
                                }
							}

					lastend++;
					if(Test.at(lastend) == ' ')
                    {
                   		lastend++;
                    }
					str3 = Test.substr(lastend, (currpos - lastend ));
					tempvec = createarguments(str3,check);
					Base* Tree2 = new Command(tempvec);
					//Tree2->addArg("\0");
                    Op = new Scolon(Tree, Tree2);
					if(check == 1)
					{
						Op->execution();
						return;
					}
					tempvec.clear();
					//cout << "This is the first command (string1)" << str1 << endl;
					//cout << "This is the first operator (string2)" << str2 << endl;
					//cout << "This is the second command (string3)" << str3 << endl;
					firstcheck = 1;
				}
			else if (Test.at(currpos) == '|')
				{
					if(Test.at(currpos + 1) == '|')
						{
							//cout << "Found you" << endl;
							str1 = Test.substr(lastend, (currpos - lastend));
							//cout << str1 << endl;
							tempvec = createarguments(str1,check);
							Base* Tree = new Command(tempvec);
							//Tree->addArg("\0");
							if(check == 1)
							{
								Op = new ORR(Tree, NULL);
								Op->execution();
								return;
							}
							tempvec.clear();
							lastend = currpos;
							str2 = Test.substr(lastend,(currpos - lastend + 2));
							tempvec = createarguments(str2,check);
							tempvec.clear();
							currpos++;
							currpos++;
							while((Test.at(currpos) != '|' && Test.at(currpos)
							!= ';' && Test.at(currpos) != '&'))
                             {
                                 currpos++;
      //                           cout << "currpos in ;: " 
      //<< currpos << "and what is at: " << Test.at(currpos) << endl;
                                if(currpos == Test.size() - 1)
                                {
                                	lastend++;
                                	lastend++;
                                	if(Test.at(lastend) == ' ')
                                	{
                                		lastend++;
                                	}
                                	str3 = Test.substr(lastend, (currpos - lastend + 1));
                                	tempvec = createarguments(str3, check);
                                	Base* Tree2 = new Command(tempvec);
                                	///Tree2->addArg("\0");
                                	Op = new ORR(Tree, Tree2);
                                	Tree = 0;
                                	Tree2 = 0;
                                	if(check == 1)
									{
										Op->execution();
										return;
									}
									tempvec.clear();
              	//cout << "This is the first command (string1)" << str1 << endl;
				//cout << "This is the first operator (string2)" <<str2 << endl;
			//cout << "This is the second command (string3)" <<str3 << endl;
									Op->execution();
                                    return;
                                }
                             }
      //cout << "currpos in |: " << currpos 
      //<< "and what is at: " << Test.at(currpos) << endl;

							
	//						cout << "currpos is at" << currpos << endl;
	//						cout << "lastend is at" << lastend << endl;
							lastend++;
							lastend++;
							if(Test.at(lastend) == ' ')
                            {
                             	 lastend++;
                            }
							str3 = Test.substr(lastend, (currpos - lastend));
							tempvec = createarguments(str3, check);
							Base* Tree2 = new Command(tempvec);
							//Tree2->addArg("\0");
                            Op = new ORR(Tree, Tree2);
                            Tree = 0;
                            Tree2 = 0;
							if(check == 1)
							{
								Op->execution();
								return;
							}
							tempvec.clear();
				//cout << "This is the first command (string1)" << str1 << endl;
				//cout << "This is the first operator (string2)" <<str2 << endl;
			//cout << "This is the second command (string3)" << str3 << endl;
							firstcheck = 1;
					}
				}
			else if (Test.at(currpos) == '&')
				{
					if(Test.at(currpos + 1) == '&')
						{
							str1 = Test.substr(lastend, (currpos - lastend));
							tempvec = createarguments(str1, check);
							Base* Tree = new Command(tempvec);
							//Tree->addArg("\0");
							if(check == 1)
							{
								Op = new ANND(Tree, NULL);
								Op->execution();
								return;
							}
							tempvec.clear();
							lastend = currpos;
							str2 = Test.substr(lastend,(currpos - lastend + 2));
							tempvec = createarguments(str2, check);
							tempvec.clear();
							currpos++;
							currpos++;
							while((Test.at(currpos) != '|' && Test.at(currpos) 
							!= ';' && Test.at(currpos) != '&'))
                             {
                                 currpos++;
//cout << "currpos in ;: "
//<< currpos << "and what is at: " << Test.at(currpos) << endl;
                                 if(currpos == Test.size() - 1)
                                {	
                                
                                	lastend++;
                                	lastend++;
                                	if(Test.at(lastend) == ' ')
                                	{
                                		lastend++;
                                	}
                                	str3 = Test.substr(lastend, 
                                	(currpos - lastend + 1));
                                	tempvec = createarguments(str3, check);
                                	Base* Tree2 = new Command(tempvec);
                                	//Tree2->addArg("\0");
                                	Op = new ANND(Tree, Tree2);
                                	Tree = 0;
                                	Tree2 = 0;
                                	if(check == 1)
									{
									Op->execution();
									return;	
									}
									tempvec.clear();
				//cout << "This is the first command (string1)" << str1 << endl;
				//cout << "This is the first operator (string2)" <<str2 << endl;
				//cout << "This is the second command (string3)" <<str3 << endl;
									Op->execution();
                                    return;
                                }
                             }


							lastend++;
							lastend++;
							if(Test.at(lastend) == ' ')
                            {
                        		lastend++;
                          	}	
							str3 = Test.substr(lastend, (currpos - lastend));
							tempvec = createarguments(str3, check);
							Base* Tree2 = new Command(tempvec);
							//Tree2->addArg("\0");
							Op = new ANND(Tree, Tree2);
							Tree = 0;
							Tree2 = 0;
							if(check == 1)
							{
								Op->execution();
								return;
							}
							tempvec.clear();
				//cout << "This is the first command (string1)" << str1 << endl;
				//cout << "This is the first operator (string2)" <<str2 << endl;
				//cout << "This is the second command (string3)" <<str3 << endl;
							firstcheck = 1;

						}
				}
			else if(currpos == (Test.size() - 1))
				{
					lastend--;
					str1 = Test.substr(lastend + 1, ((currpos + 1) - lastend));
					tempvec = createarguments(str1, check);
					Base* Tree = new Command(tempvec);
					//Tree->addArg("\0");
					Op = new Scolon(Tree, NULL);
					Tree = 0;
					if(check == 1)
					{
						Op->execution();
						return;
					}
					tempvec.clear();
					//cout << "Single line" << str1 << endl;
					Op->execution();
					return;
				}
			currpos++;
		}
//cout << "currpos is at" << currpos << endl;
//cout << "lastend is at" << lastend << endl;
lastend++;
while((Test.at(lastend) != '|' && Test.at(lastend) != ';' 
&& Test.at(lastend) != '&'))
    {
		lastend++;
   //     cout << "currpos in ;:
   //" << currpos << "and what is at: " << Test.at(currpos) << endl;
    }
if (Test.at(lastend) == ';')
{
	currpos++;
	str2 = Test.substr(lastend, (1));
	cout << str2 << endl;
	tempvec = createarguments(str2, check);
	sao = 1;
	tempvec.clear();
	lastend++;
	if(Test.at(lastend) == ' ')
    {
       lastend++;
    }
}

if (Test.at(lastend) == '|')
 {
	if (Test.at(lastend + 1) == '|')
	{
	currpos++; 
	 currpos++;
     str2 = Test.substr(lastend, (2));
     tempvec = createarguments(str2, check);
     sao = 2;
	 tempvec.clear();
     lastend++;
	 lastend++;
	if(Test.at(lastend) == ' ')
    {
       lastend++;
    }
	}
 }

if (Test.at(lastend) == '&')
 {
	if (Test.at(lastend + 1) == '&')
	{
	currpos++;
	 currpos++;
     str2 = Test.substr(lastend, (2));
     tempvec = createarguments(str2, check);
     sao = 3;
	tempvec.clear();
     lastend++;
	 lastend++;
	if(Test.at(lastend) == ' ')
    {
       lastend++;
    }
	}
 }
cout << str2 << endl;


	while(currpos != Test.size())
		{
			if (Test.at(currpos) == ';')
				{
					str1 = Test.substr(lastend, (currpos - lastend));
					tempvec = createarguments(str1, check);
					Base* tree2 = new Command(tempvec);
					//tree2->addArg("\0");
					if(sao == 1)
					{
						Base* Ops = new Scolon(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 2)
					{
						Base* Ops = new ORR(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 3)
					{
						Base* Ops = new ANND(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					if(check == 1)
					{
						Op->execution();
						return;
					}
					tempvec.clear();
					lastend = currpos;
					str2 = Test.substr(lastend, (currpos - lastend + 1));
					tempvec = createarguments(str2, check);
					sao = 1;
					tempvec.clear();
					lastend++;
					if(Test.at(lastend) == ' ')
    				{
       					lastend++;
    				}
					//cout << str1 << endl;
					//cout << str2 << endl;
				}
			else if (Test.at(currpos) == '|')
				{
					if(Test.at(currpos + 1) == '|')
						{
							str1 = Test.substr(lastend, (currpos - lastend));
							tempvec = createarguments(str1, check);
							Base* tree2 = new Command(tempvec);
							//tree2->addArg("\0");
					if(sao == 1)
					{
						Base* Ops = new Scolon(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 2)
					{
						Base* Ops = new ORR(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 3)
					{
						Base* Ops = new ANND(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					
							if(check == 1)
							{
								Op->execution();
								return;
							}
							tempvec.clear();
							lastend = currpos;
							str2 = Test.substr(lastend, (currpos - lastend + 2));
							tempvec = createarguments(str2, check);
							sao = 2;
							tempvec.clear();
							lastend++;
							lastend++;
							if(Test.at(lastend) == ' ')
    						{
    		 					lastend++;
    						}
							cout << str1 << endl;
							cout << str2 << endl;
						}
				}
			else if (Test.at(currpos) == '&')
				{
					if(Test.at(currpos + 1) == '&')
						{
							str1 = Test.substr(lastend, (currpos - lastend));
							tempvec = createarguments(str1, check);
							Base* tree2 = new Command(tempvec);
							//tree2->addArg("\0");
					if(sao == 1)
					{
						Base* Ops = new Scolon(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 2)
					{
						Base* Ops = new ORR(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 3)
					{
						Base* Ops = new ANND(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
				
							if(check == 1)
							{
								Op->execution();
								return;
							}
							tempvec.clear();
							lastend = currpos;
							str2 = Test.substr(lastend, (currpos - lastend + 2));
							tempvec = createarguments(str2, check);
							sao = 3;
							tempvec.clear();
							lastend++;
							lastend++;
							if(Test.at(lastend) == ' ')
    						{
       							lastend++;
    						}
							cout << str1 << endl;
							cout << str2 << endl;
						}
				}
			else if(currpos == (Test.size() - 1))
				{
					lastend--;
					str1 = Test.substr(lastend + 1, ((currpos + 1) - lastend));
					tempvec = createarguments(str1, check);
					Base* tree2 = new Command(tempvec);
					//tree2->addArg("\0");
					if(sao == 1)
					{
						Base* Ops = new Scolon(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 2)
					{
						Base* Ops = new ORR(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					else if(sao == 3)
					{
						Base* Ops = new ANND(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					
					if(Test.at(currpos == ';'))
					{
						Base* Ops = new Scolon(Op, tree2);
						Op = Ops;
						tree2 = 0;
						Ops = 0;
					}
					if(check == 1)
					{
						Op->execution();
						return;
					}
					tempvec.clear();
				}

		currpos++;
		}
	Op->execution();
	return;
}
	

int main()
{
	Base* Op = 0;
	//Base* Opt = 0;
	//unsigned check = 0;
	string exitstr = "exit";
	string mainstr;
	string vectorstring = "echo \"Hello all you people\"";
	vector <string> testvec;
	vector <string> testing;
	testing.push_back("echo");
	testing.push_back("\"Hello\"");
	
    //char* teststr = "echo \"Hi all\"";
    //vector <char*> testvec = createarguments(teststr);
    //cout << "Returning arguments: " << endl;
    //for(int i = 0; i <= teststr.size(); i++)
    //{
     //   wcout << teststr.at(i) << endl;
    //}
    //cout << "Start of Program" << endl;
    //testvec = createarguments(vectorstring, check);
    //cout << "testvec created" << endl;
    //cout << "Testing function success" << endl;
    //for(unsigned i = 0; i < testvec.size(); i++)
    //{
    //	cout << testvec.at(i) << endl;
    //}
    while (mainstr != exitstr)
    {
    string mainstr = "";

    //cout << "Please enter command: " << endl;
    getline (cin, mainstr);
        if (mainstr == exitstr)
    {
    	return 0;
    }
	//cout << " Current string: " << mainstr << endl;
	breakstring(mainstr, Op);
	Op = 0;
	//cout << "String Broken" << endl;
	//Op->execution();
	// Base* T1 = new Command(testing);
	// T1->addArg("\0");
	// Base* T2 = new Command(testing);
	// T2->addArg("\0");
	// Base* Test = new Scolon(T1, T2);
	// T1 = 0;
	// T2 = 0;
	// Test->execution();
    }
   return 0;
}
