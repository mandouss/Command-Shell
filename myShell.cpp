#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <string>
#include <vector>
#include "split.h"
#include "find.h"
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
	vector<char*>  vc;
	transform(env_vec.begin(), env_vec.end(), std::back_inserter(vc), convert); 
	for( size_t i = 0; i < env_vec.size(); ++i )
	{ 
	  	cout<<env_vec[i]<<endl;
	 }

	while(1)
	{
		//output the shell
		cout<<"myShell $ ";
		string input;
		//get the input 
		getline(cin,input);
		pid_t child_pid = fork();	
		if(child_pid >= 0)
		{	
			//if it is child process
	 		if(child_pid == 0)
			{
				if(input.find_first_of('/') == string::npos)
				{
					for(int i = 0; i < env_vec.size(); i++)
					{
						if(findFile(input,env_vec[i]))
						{

							string command = env_vec[i]+'/'+input;
							char *cstr = new char[command.length() + 1];
							strcpy(cstr, command.c_str());
							char *env =  new char[input.length() + 1];
							strcpy(env, input.c_str());
							char *args[] = {env,NULL};
							return execve(cstr,args,NULL);
						}
					}
					cout<<"Command "<<input<<" not found"<<endl;
					return -1;
				}
				else
				{
					char *cstr = new char[input.length() + 1];
					strcpy(cstr, input.c_str());
    				return execve(cstr,NULL,NULL);
				}
				
			}
			//parent process
			else
			{
				int status;
				waitpid(child_pid,&status,0);
				if(input == "exit")
					break;
				else
				{
					if(WIFSIGNALED(status))
					{
						cout<<"Program was killed by signal "<<WTERMSIG(status)<<endl;
						continue;
					}						
					else
					{
						cout<<"Program was killed by state "<<status<<endl;
						continue;
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
