#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <string>
using namespace std;
int main()
{
	
	//int status;
	//cout<<"myshell";
	while(1)
	{
		//output the shell
		cout<<"myShell $ ";
		string input;
		//get the input 
		getline(cin,input);
		char *cstr = new char[input.length() + 1];
		strcpy(cstr, input.c_str());
		pid_t child_pid = fork();	
		if(child_pid >= 0)
		{	
	 		if(child_pid == 0)
			{
				return execve(cstr,NULL,NULL);
			}
			else
			{
				int status;
				pid_t sign = waitpid(child_pid,&status,0);
				if(input == "exit")
					break;
				else
				{
					if(WIFSIGNALED(status))
						cout<<"Program was killed by signal "<<WTERMSIG(status)<<endl;
					cout<<"Program was killed by state "<<status<<endl;
					continue;	
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