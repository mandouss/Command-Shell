#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include "split.h"
#include "find.h"

extern char **environ;
using namespace std;

char *convert(const string & s)
{
   char *pc = new char[s.size()+1];
   std::strcpy(pc, s.c_str());
   return pc; 
}

int main()
{

	string env = getenv("PATH");
	vector<string> env_vec;
	char colon = ':';
	splitBySymbol(env,env_vec,colon);
	// for( size_t i = 0; i < env_vec.size(); ++i )
	// { 
	//   	cout<<env_vec[i]<<endl;
	//  }
	while(1)
	{
		//output the shell
		cout<<"myShell $ ";
		string input;
		bool findCommand = false;
		bool absolute = false;
		//get the input 


		getline(cin,input);
		vector<string> args_vec;
		splitBySpace(input,args_vec);
		cout<<args_vec.size()<<endl;
		if(cin.eof())
		{
			cout<<endl;
			return EXIT_SUCCESS;
		}
		char *cmd;
		char *arg;
		char **args;
		args = new char*[args_vec.size()+1];
		//set the args
		for(int i = 1 ; i < args_vec.size();i++)
		{
			char *temp = new char[args_vec[i].length()+1];
			strcpy(temp, args_vec[i].c_str());
			args[i] = temp;
		}
		args[args_vec.size()] = NULL;
		if(input.find_first_of('/') == string::npos)
			{
				//dealing with the path which doesn't has /
				for(int i = 0; i < env_vec.size(); i++)
				{
					if(findFile(args_vec[0],env_vec[i]))
					{
						string command = env_vec[i]+'/'+args_vec[0];
						cmd = new char[command.length() + 1];
						strcpy(cmd, command.c_str());
						arg =  new char[args_vec[0].length() + 1];
						strcpy(arg, args_vec[0].c_str());
           				args[0] = arg;
           				findCommand = true;
           				break;
					
					}
				}
			}
		else
			{
				cmd = new char[args_vec[0].length()+1];
				strcpy(cmd, args_vec[0].c_str());
				//if it is absolute path
				if(args_vec[0].find("./") == string::npos)
				{
					int last = args_vec[0].find_last_of("/");
					arg =  new char[args_vec[0].length()-last];
					substring(args_vec[0].c_str(),last+1,args_vec[0].length(),arg);
           			args[0] = arg;
           			cout<<arg;
					absolute = true;
				}
			}			

			// cmd = new char[args_vec[0].length()+1];
			// strcpy(cmd, args_vec[0].c_str);
			// args = new char*[args_vec.size()];
			// for(int i = 1; i < args_vec.size();i++ )
			// {
			// 	args
			// }
		
		// else
		// {
		// 	vector<string> args;
		// 	char space = ' ';
		// 	splitBySymbol(input,args,space);
		// 	for( size_t i = 0; i < args.size(); ++i )
		// 	{ 
	 //  			cout<<args[i]<<endl;
		// 	}

		// }




		pid_t child_pid = fork();	
		if(child_pid >= 0)
		{	
			//if it is child process
	 		if(child_pid == 0)
			{
				if(input.find_first_of('/') == string::npos)
				{
					if(findCommand)
					{
						//find command in PATH
						return execve(cmd,args,environ);
					}
					else
					{
						if(input != "exit" && !cin.eof())
						{
							cout<<"Command "<<input<<" not found"<<endl;
						}
						return -1;
					}
				}
				else
				{	
					if(absolute)
					{
						cout<<"absolute path"<<endl;
						cout<<args[0];
						cout<<args[1];
						return execve(cmd,args,NULL);
					}
					else
					{
						return execve(cmd,NULL,NULL);
					}

				}				
			}
			//parent process
			else
			{
				int status;
				waitpid(child_pid,&status,0);
				if(input == "exit")
				{
    				delete cmd;
					delete arg;
					delete [] args;	
					break;
				}
				else
				{
					if(WIFSIGNALED(status))
					{
      					cout<<"Program was killed by signal "<<WTERMSIG(status)<<endl;
    				}
    				else
    				{
      					cout<<"Program exited with status "<<WEXITSTATUS(status)<<endl;
    				}

				}	
			}		
	 	}
	 	else
	 	{
	 		perror("fork failed");
	 	}

	}

	return 0;
}
