#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int a = argc;
	for (int i =0; i < argc; i++) 
	{
 		printf ("Arg %d is %s\n", i, argv[i]);
 	}
	cout<<"hello, this is a arg test program!"<<endl;
	return 0;
}
