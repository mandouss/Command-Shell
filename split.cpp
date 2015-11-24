#include "split.h"
//it is a split function that can split string into vector 
//by a specific symbol
//has consider the "repeat symbols" situation 
void splitBySymbol(string s, vector<string>& ret,char symbol)  
{  
    size_t last = 0;
    size_t first = 0;
    first=s.find_first_not_of(symbol,last);
    last =s.find_first_of(symbol,first);
    while (last!=std::string::npos)
    {
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

//get substring of a sting
void substring(char const*s,int i,int n,char *t)
{
 	int j=0;
 	for(;j<n;j++)
  		t[j]=s[i++];
 	t[j]=0;
}

//delete all space in command and split the command into vector
//ignore the first space follow the '/' symbol
void splitBySpace(string s, vector<string>& ret)
{
	int first = 0;
	int current = 0;
	for(current = 0; current < s.length();current++)
	{
		if(s.at(current) == ' ')
		{
			if(current == first)
			{
				++first;
				continue;
			}
			else if(s.at(current-1) == '/')
			{
				if(current != s.length()-1)
					continue;
				else
				{
					char *in = new char[current-first+1];
					s.copy(in,current-first+1,first);
					in[current-first+1]='\0';
					string put(in);
					delete in;
					ret.push_back(put);
					if(current+1 < s.length())
					first = current+1;						
				}
			}
			else
			{
				char *in = new char[current-first];
				s.copy(in,current-first,first);
				in[current-first] = '\0';
				string put(in);
				delete in;
				ret.push_back(put);
				if(current+1 < s.length())
				first = current+1;

			}
		}
		else 
		{
			if(current ==s.length()-1)
			{
				char *in = new char[current-first+1];
				s.copy(in,current-first+1,first);
				in[current-first+1]='\0';
				string put(in);
				delete in;
				ret.push_back(put);
				if(current+1 < s.length())
				first = current+1;				

			}
		}
		
	}
}

