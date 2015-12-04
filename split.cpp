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
char* substring(char const*s,int i,int n)
{
  char* result = new char[n-i+1];
  int j=0;
  int b = i;
  for(;j<n-i;j++)
    {
      result[j]=s[b++];
    }
  result[j] = '\0';
  return result;

}

//delete all space in command and split the command into vector
//ignore the first space follow the '\' symbol
void splitBySpace(string s, vector<string>& ret)
{

        size_t current = 0;
	string to_add;
	for(current = 0; current < s.length();current++)
	{
	  //check whether current is '\' symbol
	  if(s.at(current) == '\\')
	    {
	      //check whether space is follow '\' symbol
	      if(current < s.length()-1 && s.at(current+1) == ' ')
		{
		  to_add.append(" ");
		  current +=1;
		}
	    }
	  else if(s.at(current) == ' ')
	    {
	      if(to_add != "")
	      ret.push_back(to_add);
	      to_add = "";
	    }
	  else 
	    {
	      to_add.append(1,s.at(current));
	      if(current ==s.length()-1)
		{
		  ret.push_back(to_add);
		}
	    }
	  
	}
}

