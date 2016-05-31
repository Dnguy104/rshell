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

Base* treecreate(vector <vector <string> > cmds, vector <vector <string> > ops, 
Base *& op, unsigned & count, unsigned & currint, unsigned & level)
{// function that reads from the vectors and creates a tree that can be read 
//from the execute file. the code also does post liminary clean up on the 
//vectors and commands
//recursive


   // cout << "count: " << count << endl;
    //cout << "Level: " << level << endl;
    //cout << "currint: " << currint<< endl;
    stringstream ss;
    string testchk = "test";
    vector <string> Node;
    string temp;
    int recursfound = 0;
    unsigned i = 0;
    Base* Ops = NULL;
    Base* Opt = NULL;
    //Base* Br1 = NULL;
    //Base* Br2 = NULL;
    
    ss << cmds[count].at(i);
    if(ss >> temp)
    {
       // cout << "count: " << count << endl;
        //cout << "Curr temp left: " << temp << endl;
        if (temp == "Recurse")
        {
            level++;
            currint++;
            count = level;
            Ops = treecreate(cmds, ops, op, count, currint, level);
           // cout << "exit recurse3" << endl;
            currint--;
            count = currint;
            
        }
        else if(temp == "[")
        {
           // cout << "found test bracket" << endl;
            Node.push_back("test");
            while(ss >> temp)
            {
              //  cout << "Curr temp left: " << temp << endl;
                if(temp != "]")
                {
                Node.push_back(temp);
                }
            }
          //  cout << "creating node" << endl;
            // for (unsigned q; q < Node.size(); q++)
            // {
            //     cout << Node.at(q) << endl;
            // }
             Ops = new Command(Node);
        }
        else if(temp == "]")
        {
        }
        else if(temp == " ")
        {
            Ops = NULL;
        }
        else
        {
            Node.push_back(temp);
            while(ss >> temp)
            {
              //  cout << "Curr temp left: " << temp << endl;
                Node.push_back(temp);
            }
          //  cout << "creating node" << endl;
            Ops = new Command(Node);
        }
    }
    //cout << "count: " << count << endl;
    //cout << "   got left" << endl;
    ss.str( string() );
    ss.clear();
    Node.clear();
    i++;
    //cout << "count: " << count << endl;
   // cout << "   getting right" << endl;
     //cout << "size" << cmds[count].size() <<endl;
    if((cmds[count].size())  > 1)
    {
       // cout << "entered" << cmds[count].size() <<endl;
        ss << cmds[count].at(i);
      //  cout << "found" << endl;
    while(ss >> temp && recursfound == 0)
    {
        
        //cout << "Curr temp right: " << temp << endl;
        if (temp == "Recurse")
        {
            level++;
            currint++;
            count = level;
            Opt = treecreate(cmds, ops, op, count, currint, level);
            //cout << "exit recurse2" << endl;
            currint--;
            recursfound = 1;
            count = currint;
        }
        else if(temp == " ")
        {
            Opt = NULL;
        }
        else if(temp == "[")
        {
           // cout << "found test bracket" << endl;
            Node.push_back(testchk);
        }
        else if(temp == "]")
        {
        }
        else if(temp == "1")
        {
                        i++;
           // cout << "found 1" << endl;
            if(cmds[count].size() >= 3)
            {
            //i++;
            ss << cmds[count].at(i);
            //ss >> temp;
            //Node.push_back(temp);
            //cout << "curr temp:" << temp << endl;
            }
            else
            {
                //cout << "NULLED" << endl;
                Opt = NULL;
            }
        }
        else
        {
            Node.push_back(temp);
            while(ss >> temp)
            {
               // cout << "Curr temp right: " << temp << endl;
                Node.push_back(temp);
            }
            Opt = new Command(Node);
        }
    }
    //cout << "count: " << count << endl;
    //cout << "   got right" << endl;
    ss.str( string() );
    ss.clear();
    Node.clear();
    }
    else
    {
       // cout << "   null right" <<endl;
        Opt = NULL;
    }
    //cout << "   getting op" << count << endl;
    //cout << "ops size" << ops.size() << endl;
    if(!ops[count].empty())
    {
     //   cout << "entered" << endl;
        ss << ops[count].at(0);
    //cout << "Currently at op 0: " << ops[count].at(0) << endl;
    if(ss >> temp)
    {
        //cout << "Curr temp: " << temp << endl;
        Node.push_back(temp);
        if(temp == "&&")
        {
            //cout << "create link &&" << endl;
            op = new ANND(Ops, Opt);
        }
        else if(temp == "||")
        {
            op = new ORR(Ops, Opt);
        }
        else
        {
            op = new Scolon(Ops, Opt);
        }
        
    }
    else
    {
        //cout << "create default scolon link" << endl;
        op = new Scolon(Ops, Opt);
    }
    }
    else
    {
        //cout << "standardizing op scolon" << endl;
        op = new Scolon(Ops, Opt);
       // cout << "created op" << endl;
        //cout << "returning" << endl;
        //return op;
    }
    //cout << "count: " << count << endl;
    //cout << "   got op" << endl;
    Ops = NULL;
    Opt = NULL;
    ss.str( string() );
    ss.clear();
    Node.clear();
    //cout << "count: " << count << endl;
    //cout << "entering loop" << endl;
    //cout << "size: " << cmds[count].size() << endl;
  //  cout << "i = " << i << endl;
    i++;
    while (i < cmds[count].size() )
    {
        //cout << "loop" << endl;
        Ops = op;
        //cout << "for loop" << endl;
        if((cmds[count].size()) != i)
        {
            ss << cmds[count].at(i);
           // cout << "if statment" << endl;
            //ss << cmds[count].at(i + 1);
            if(ss >> temp)
            {
              //  cout << "Curr temp left: " << temp << endl;
                if (temp == "Recurse")
                {
                    level++;
                    currint++;
                    count = level;
                  //  cout << "recursing" << endl;
                    Opt = treecreate(cmds, ops, op, count, currint, level);
                  //  cout << "exit recurse1" << endl;
                    currint--;
                    count = currint;
                }
                else if(temp == " ")
                {
                 //   cout << "Nullifying" << endl;
                    Opt = NULL;
                }
                else if(temp == "[")
                {
                //    cout << "found test bracket" << endl;
                    Node.push_back(testchk);
                }
                else if(temp == "]")
                {
                }
                else if(temp == "1")
                 {
              //       cout << "found 1" << endl;
                    if(cmds[count].size() > i + 1)
                    {
                    ss << cmds[count].at(i + 1);
                    ss >> temp;
                    }
                    else
                    {
                        Opt = NULL;
                    }
               }
                else
                {
                    Node.push_back(temp);
                    while(ss >> temp)
                    {
                        //cout << "Curr temp left: " << temp << endl;
                        Node.push_back(temp);
                    }
                   // cout << "command node created Opt" << endl;
                    Opt = new Command(Node);
                }
            }        
            ss.str( string() );
            ss.clear();
            Node.clear();
           // cout << "   got leftg" << endl;
        }
       // cout << "past commands" << endl;
      //  cout << "i = " << i << endl;
        if(i < ops[count].size())
        {
           //cout << "entered iff statment" << ops[count].at(i) << endl;
            if(!ops[count].at(i).empty())
            {
               // cout << "finding" << endl;
                ss << ops[count].at(i);
            }
            else
            {
           //     cout << "standardizing op scolon" << endl;
                op = new Scolon(Ops, Opt);
                Ops = op;
            }
      //  cout << "Currently at op" << i << ": " << ops[count].at(i) << endl;
        if(ss >> temp)
        {
          //  cout << "Curr temp right: " << temp << endl;
            Node.push_back(temp);
            if(temp == "&&")
            {
                op = new ANND(Ops, Opt);
                Ops = op;
            }
            else if(temp == "||")
            {
                op = new ORR(Ops, Opt);
                Ops = op;
            }
            else
            {
                op = new Scolon(Ops, Opt);
                Ops =op;
            }
        
        }
        else
        {
            op = new Scolon(Ops, Opt);
            Ops = op;
        }
        }
        else
        {
          //  cout << "standardizing op scolon" << endl;
            op = new Scolon(Ops, Opt);
            Ops = op;
        }
        //cout << "   got op" << endl;
       //cout << "looping" << endl;
       op = Ops;
       Ops = NULL;
       
       i++;
    }
  //  cout << "loop finished" << endl;
        ss.str( string() );
        ss.clear();
        Node.clear();
        Ops = NULL;
        Opt = NULL;
    
    
  //  cout << "returning" << endl;

    return op;
}
//--------------------------------Function start-----------------------//

void breakup(string test, vector <vector <string> > & cmds, 
vector <vector <string> > & ops, unsigned & rct, unsigned & nbc, unsigned & lrc)
{
//code that parses through the givin command, and isolates and organizes the
//commands and operators into respective vectors and respective locations
//recursive
    cmds.push_back(vector <string>());
    ops.push_back(vector <string>());
    string curr;
    string temp;
    string recur;
    stringstream ss;
    stringstream testss;
    stringstream cmd;
    string wholecmd;
    string check = "Recurse";
    ss << test;
   // cout << "       current rct/nbc: " << endl;
   // cout << rct << " / " << nbc << endl;


    
    while(ss >> curr)
    {
       // cout << "           Overhead curr: " << curr << endl;
        if((curr != "||") && (curr != "&&") && (curr != ";") )
        {
            //cout << "found no op" << endl;
           // cout << "curr is: " << curr << endl;
            
            for(unsigned i = 0; i < curr.size(); i++)
            {
            //    cout << "Current i is: " << curr.at(i) << endl; 
                if(curr.at(i) == '(') //start parenth check -
                {
                    if(curr.size() == 1) //parenth organizers --start
                    {
                        ss >> curr;
                        i = 0;
                    }
                    else if( i == curr.size() - 1)
                    {
                        curr = curr.substr(0, i);
                        cmd << curr;
                        cmd << " ";
                        ss >> curr;
                        i = 0;
                    }
                    else if (i == 0)
                    {
                        curr = curr.substr(1, curr.size() - 1);
                     //   cout << "new curr: " << curr << endl;
                        i = 0;
                    }
                    else
                    {
                        temp = curr.substr(0, i);
                        cmd << temp;
                        cmd << " ";
                        curr = curr.substr(i + 1, (i - (curr.size() - 1)));
                        i = 0;
                    }                   //parenth organizers --end
                    //cout << "finished organization" << endl;
                    unsigned numparent = 1; //find ending parenth ---start
                    while(numparent != 0)
                    {
                       // cout << "nummparent: " << numparent << endl;
                        if (curr.at(i) == ')')
                        {
                            //cout << "found end par" << endl;
                            numparent--;
                            if(i == curr.size() - 1)
                            {
                                if(numparent == 0)
                                {
                                    curr = curr.substr(0, i);
                                }
                            testss << curr;
                            testss << " ";
                            //ss >> curr;
                            i = 0;
                            }
                            else
                            {
                            i++;
                            }
                        }
                        else if (curr.at(i) == '(')
                        {
                           // cout << "found begin par" << endl;
                            numparent++;
                            i++;
                        }
                        else if( i == curr.size() - 1)
                        {
                          //  cout << "found end" << endl;
                            testss << curr;
                            testss << " ";
                            ss >> curr;
                            i = 0;
                        }
                        else
                        {
                            i++;
                        }
                        //cout << "curr at i: " << curr.at(i) << endl;
                    }
                   // cout << "finished counting" << endl;
                    if( i != 0)
                    {
                        //cout << "end parent is in last word" << endl;
                        //cout << "current curr: " << curr << endl;
                        curr = curr.substr(0, i - 1);
                        //cout << "new curr: " << curr << endl;
                        testss << curr;
                    }
                    recur = testss.str(); //find ennding parenth ---end
                    testss.str( string() );
                    testss.clear();
                    //cout << "       current rct/nbc: " << endl;
                   // cout << rct << " / " << nbc << endl;                    
                    
                    lrc++;
                    nbc++;
                    
                //    cout << "       String to be sent: " << endl;
                 //   cout << recur << endl;
                //    cout << "       current rct/nbc: " << endl;
                 //   cout << rct << " / " << nbc << endl;
                    cmd << check;
                    cmd << " ";
                    cmd << nbc;
                    wholecmd = cmd.str();
                   // cout << "current rct before pushback: " << rct << endl;
                    cmds[rct].push_back(wholecmd);
                    cmd.str( string() );
                    cmd.clear();
                    rct = nbc;
                 //   cout << "       RECURSING" << endl;
                    breakup(recur, cmds, ops, rct, nbc, lrc);
                 //   cout << "       ENDING RECURSE" << endl;
                    lrc--;
                    rct = lrc;
                //    cout << "       new rct/nbc: " << endl;
             //       cout << rct << " / " << nbc << endl;

                    
                    curr = "1 ";
                    i = curr.size();              // end recurstion part --
                    // cout << " what is next curr? : " << endl;
                    // ss >> curr;
                    // cout << curr << endl;
                    
                }
                else if(curr.at(i) == '"')
                {
                //cout << "encountered quote in " << curr <<  endl;
                    if(curr.size() == 1)
                    {
                   //     cout << "1" << endl;
                        ss >> curr;
                    }
                    else
                    {
                      //  cout << ">1" << curr.size() << endl;
                        curr = curr.substr(1, curr.size());
                     //   cout << "new curr" << curr <<endl;
                    }

                        i = 0;
                        cmd << " ";
                       // cout << "old curr" << curr <<  endl;
                        
                        //ss >> curr;
                     //   cout << "New curr: (space) " << curr << endl;
                    
                    while(curr.at(i) != '"')
                    {
                       // cout << "while looping" << endl;
                        //cout << "found: " << curr.at(i) << endl;
                        if(i == (curr.size() - 1))
                        {
                            i = 0;
                            cmd << curr;
                            cmd << " ";
                            if(ss >> curr)
                            {
                         //  cout << "New curr: (std) " << curr << endl;
                            }
                            //cout << "switched to next curr" << endl;
                        }
                        if(i < curr.size() - 1)
                        {
                           // cout << "increased" << endl;
                            //cout << "at i: " << curr.at(i) << endl;
                            i++;
                        }
                    }
                    if(curr.at(i) == '"')
                    {
                        //cout << "Deleted parent" << endl;
                        curr.at(i) = '\0';
                    }
                }
                else if(curr.at(i) == '#')
                {
                    //cout << "   found pound in " << curr <<endl;
                    if(i == 0)
                    {
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);cmd.str( string() );
                         cmd.str( string() );
                        cmd.clear();
                        return;
                    }
                    else
                    {
                    curr = curr.substr(0, i);
                    cmd << curr;
                    //cout << "   curr before pound " << curr <<endl;
                    wholecmd = cmd.str();
                    cmds[rct].push_back(wholecmd);
                    cmd.str( string() );
                    cmd.clear();
                    
                    return;
                    }
                }
                else if(curr.at(i) == ';')
                {
                    //cout << "   found embeded op" << endl;
                    if(i == 0)
                    {
                      //  cout << "   Found something after" << endl;
                        temp = curr.at(i);
                        //cout << "Temp is now: " << temp << endl; 
                        curr = curr.substr(1, curr.size() -1);
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);
                        ops[rct].push_back(temp);
                        cmd.str( string() );
                        cmd.clear();
                        i = 0;
                        
                    }
                    else
                    {
                        if(i != curr.size() - 1)
                        {
                        //    cout << "   Found things before and after" 
                        //<< endl;
                            temp = curr.substr(i, i - curr.size() - 1);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            curr = temp.substr(1, temp.size() - 1);
                            temp = temp.substr(0, 1);
                            ops[rct].push_back(temp);
                            i = 0;
                            
                            
                        }
                        else
                        {
                            //cout << "   Found something before" << endl;
                            temp = curr.at(i);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            ops[rct].push_back(temp);
                               // cout << "continuing" << endl;
                                curr = " ";
                                i = curr.size();
                        }
                        
                    }
                }
                else if(curr.at(i) == '|')
                {
                    //cout << "   found embeded op" << endl;
                    if(i == 0)
                    {
                      //  cout << "   Found something after" << endl;
                        temp = curr.substr(0, 2);
                        //cout << "Temp is now: " << temp << endl; 
                        curr = curr.substr(2, curr.size() -1);
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);
                        ops[rct].push_back(temp);
                        cmd.str( string() );
                        cmd.clear();
                        i = 0;
                        
                    }
                    else
                    {
                        if(i != curr.size() - 2)
                        {
                          //  cout << "   Found things before and after" 
                          //<< endl;
                            temp = curr.substr(i, i - curr.size() - 1);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            curr = temp.substr(2, temp.size() - 1);
                            temp = temp.substr(0, 2);
                            ops[rct].push_back(temp);
                            i = 0;
                            
                            
                        }
                        else
                        {
                           // cout << "   Found something before" << endl;
                            temp = curr.substr(i, 2);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            ops[rct].push_back(temp);

                                curr = " ";
                                i = curr.size();

                        }
                        
                    }
                }
                else if(curr.at(i) == '&')
                {
                    //cout << "   found embeded op" << endl;
                    if(i == 0)
                    {
                      //  cout << "   Found something after" << endl;
                        temp = curr.substr(0, 2);
                        //cout << "Temp is now: " << temp << endl; 
                        curr = curr.substr(2, curr.size() -1);
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);
                        ops[rct].push_back(temp);
                        cmd.str( string() );
                        cmd.clear();
                        i = 0;
                        
                    }
                    else
                    {
                        if(i != curr.size() - 2)
                        {
                           //cout << "   Found things before and after" << endl;
                            temp = curr.substr(i, i - curr.size() - 1);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            curr = temp.substr(2, temp.size() - 1);
                            temp = temp.substr(0, 2);
                            ops[rct].push_back(temp);
                            i = 0;
                            
                            
                        }
                        else
                        {
                           // cout << "   Found something before" << endl;
                            temp = curr.substr(i, 2);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            ops[rct].push_back(temp);

                                curr = " ";
                                i = curr.size();
      
                        }
                        
                    }
                }
                
            }
            if(curr.at(curr.size() - 1) == '"')
            {
            curr.at(curr.size() - 1) = '\0';
            }

        //    cout << "New curr (end) :" << curr << endl;
            cmd << curr;
            cmd << " ";
        }
        else
        {
        //    cout << "found op" << endl;
       //     cout << "current level: " << endl;
          //  cout << rct << " / " << nbc << endl;
            wholecmd = cmd.str();
            cmds[rct].push_back(wholecmd);
            ops[rct].push_back(curr);
            cmd.str( string() );
            cmd.clear();
        }
        //cout << curr << endl;
    }
    //cout << "finalizing" << endl;
    //cout << "Cmd: " << cmd.str() << endl;
    wholecmd = cmd.str();
    //cout << "current rct: " << rct << endl;
    cmds[rct].push_back(wholecmd);
    cmd.str( string() );
    cmd.clear();
    
    return;
}
    
//---------------------------------Main start-----------------------------//

int main()
{
    
    string testcmd = "echo \"false\" && echo \"true\" || echo \"true\" ";
    vector <vector <string> > cmds;
    vector <vector <string> > ops;
    Base* op;
    string exitstr = "exit";
    string mainstr;
    unsigned recurstrack = 0;
    unsigned numbcalls = 0;
    unsigned count = 0;
    unsigned currint = 0;
    unsigned level = 0;
    unsigned levelrc = 0;
    
    //breakup(testcmd, cmds, ops,  recurstrack, numbcalls, levelrc);
    
   
   
    //op = treecreate(cmds, ops, op, count, currint, level);
    
    
   // op->execution();
    
   
    
    char HOST[128];
    gethostname(HOST, sizeof HOST);
    char *USER = getlogin(); 
    //cout << "before while loop" << endl;
    while (mainstr != exitstr)
    {
        //cout << "entered while loop" << endl;
        string mainstr = "";
        // cout << "after mainstr" << endl;
        cout << USER << "@" << HOST << "$ ";
        // cout << "Please enter command: " << endl;
        getline (cin, mainstr);
            if (mainstr == exitstr)
        {
            return 0;
        }
        //cout << " Current string: " << mainstr << endl;
        breakup(mainstr, cmds, ops,  recurstrack, numbcalls, levelrc);
//      cout << "we broke up" << endl;
//      for(unsigned i = 0; i < cmds.size(); i++)
//         {
//             for(unsigned j = 0; j < cmds[i].size(); j++)
//             {
//                 cout << "for cmd: " << i << " , " << j << " it is:" << endl;
//                 cout << cmds[i][j] << endl;
//             }
//             cout << endl;
//         }
    
//         cout << "ops list:" << endl;
        
//         for(unsigned a = 0; a < ops.size(); a++)
//         {
//             for(unsigned b = 0; b < ops[a].size(); b++)
//             {
//                 cout << "for op: " << a << " , " << b << " it is:" << endl;
//                 cout << ops[a][b] << endl;
//             }
//             cout << endl;
//         }
    
//          cout << "opsize" << ops.size() <<endl;
//          cout << "cmdsize" << cmds.size() <<endl;
    
        op = treecreate(cmds, ops, op, count, currint, level);
        // cout <<endl;
              op->execution();
      
        
        op = 0;
        recurstrack = 0;
        numbcalls = 0;
        count = 0;
        currint = 0;
        level = 0;
        levelrc = 0;
        cmds.clear();
        ops.clear();
    

    }
    
    return 0;
}

