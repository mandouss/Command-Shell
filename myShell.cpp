#include <iostream>
#include <string>
using namespace std;
int main()
{
	while(cin){
		string input;
		cout<<"myShell $ ";
		getline(cin,input);
		if(input == "exit")
			break;
		else
			cout<<input<<endl;
		 

	}
	return 0;
}