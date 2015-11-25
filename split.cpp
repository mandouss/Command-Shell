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
 	//t[j]='\0';
}

//delete all space in command and split the command into vector
//ignore the first space follow the '/' symbol
void splitBySpace(string s, vector<string>& ret)
{
	size_t first = 0;
        size_t current = 0;
	for(current = 0; current < s.length();current++)
	{
		if(s.at(current) == ' ')
		{
			//situation:have space at first
			if(current == first)
			{
				++first;
				continue;
			}
			//situation: find space, but has '/' before, 
			//situation: find space at the last, but has '/' before
			else if(s.at(current-1) == '\\')
			{
				if(current != s.length()-1)
					continue;
				else
				{
					char *in = new char[current-first+2];
					s.copy(in,current-first+1,first);
					in[current-first+1]='\0';
					string put(in);
					delete[] in;
					ret.push_back(put);
					if(current+1 < s.length())
					first = current+1;						
				}
			}
			//situation: find space, push command into vector
			else
			{
			  char *in = new char[current-first+1];
			  s.copy(in,current-first,first);
			  in[current-first] = '\0';
			  string put(in);
			  delete[] in;
			  ret.push_back(put);
			  if(current+1 < s.length())
			  first = current+1;
			  
			}
		}

		else 
		{
			//situation: one command without space
			//situation: command at the last,with no space in the end
			if(current ==s.length()-1)
			{
				char *in = new char[current-first+2];
				s.copy(in,current-first+1,first);
				in[current-first+1]='\0';
				string put = in;
				delete[] in;
				ret.push_back(put);
				if(current+1 < s.length())
				first = current+1;				

			}
		}
		
	}
}

