#ifndef __SPLIT_H__
#define __SPLIT_H__
#include <iostream>
#include <vector>

#include <sys/ptrace.h>
#include <string>
using namespace std;
void splitBySymbol(string s, vector<string>& ret, char symbol);  
char* substring(char const*s,int i,int n);
void splitBySpace(string s, vector<string>& ret);

#endif
