#ifndef __DIR_H__
#define __DIR_H__
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <stack>
#include "split.h"
using namespace std;
bool changeDir(string command,string args,stack<string>& paths);

#endif
