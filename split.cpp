#include "split.h"
//it is a split function that can split string into vector 
//by a specific symbol 
void splitBySymbol(string s, vector<string>& ret,char symbol)  
{  
    size_t last = 0;
    size_t first = 0;
    first=s.find_first_not_of(symbol,last);
    last =s.find_first_of(symbol,first);
    while (last!=std::string::npos)
    {
    	// string result;
    	// if(symbol == ':')
    	// {
    	// 	result = "PATH=" + s.substr(first,last-first);
    	// }
        ret.push_back(s.substr(first,last-first));
        first=s.find_first_not_of(symbol,last);
        last =s.find_first_of(symbol,first);
    }
    if (first - last>0)
    {
        ret.push_back(s.substr(first,last));
    }
    return;

}

