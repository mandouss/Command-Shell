#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <string>
#include <vector>
#include "split.h"
using namespace std;
char *convert(const std::string & s)
{
   char *pc = new char[s.size()+1];
   std::strcpy(pc, s.c_str());
   return pc; 
}

int main()
{
	

	// vector<string> result;
	// string s = ",,,,qwejqle,,,,,3132313";
	// char symbol = ',';
	// splitBySymbol(s,result,symbol);

	string env = getenv("PATH");
	vector<string> env_vec;
	char colon = ':';
	splitBySymbol(env,env_vec,colon);
	//const char *env_char[env_vec.size()];
	vector<char*>  vc;
	transform(env_vec.begin(), env_vec.end(), std::back_inserter(vc), convert); 
	// for( size_t i = 0; i < v.size(); ++i )
	// { 
	//  	v[i] = env_vec[i].c_str(); 
	//  }

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
			//if it is child process
	 		if(child_pid == 0)
			{

				// for(int i = 0; &vc[i] != NULL; i++)
				// {
				// 	int a = execve(cstr,NULL,&vc[3]);
				// 	cout<<a<<endl;
				// }
				return execve(cstr,NULL,&vc[3]);
				
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
