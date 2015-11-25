#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, char **argv)
{
	
	for (int i =0; i < argc; i++) 
	{
 		printf ("Arg %d is %s\n", i, argv[i]);
 	}
	cout<<"hello, this is a arg test program!"<<endl;
	return 0;
}
