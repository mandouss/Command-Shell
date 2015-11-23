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
	for( size_t i = 0; i < env_vec.size(); ++i )
	{ 
	  	cout<<env_vec[i]<<endl;
	 }
	while(1)
	{
		//output the shell
		cout<<"myShell $ ";
		string input;
		bool findCommand = false;
		bool absolute = false;
		//get the input 


		getline(cin,input);
		if(cin.eof())
		{
			cout<<endl;
			return EXIT_SUCCESS;
		}
		char *cmd;
		char *arg;
		char **args;
		if(input.find_first_of('/') == string::npos)
		{
			for(int i = 0; i < env_vec.size(); i++)
			{
				if(findFile(input,env_vec[i]))
				{
					string command = env_vec[i]+'/'+input;
					cmd = new char[command.length() + 1];
					strcpy(cmd, command.c_str());
					arg =  new char[input.length() + 1];
					strcpy(arg, input.c_str());
					args = new char* [1+1];
           			args[0] = arg;
           			args[1] = NULL;
           			findCommand = true;
           			break;
					
				}
			}
		}
		else
		{
			cmd = new char[input.length()+1];
			strcpy(cmd, input.c_str());
			if(input.find("./") == string::npos)
			{
				int last = input.find("/");
				arg =  new char[input.length()-last + 1];
				substring(input.c_str(),last,input.length(),arg);
				args = new char* [1+1];
           		args[0] = arg;
           		args[1] = NULL;	
				absolute = true;

			}

		}



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
