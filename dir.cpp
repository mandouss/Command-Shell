#include "dir.h"
bool changeDir(string command,string args,stack<string>& paths)
{
	if(command == (string("cd")))
	{
      int ret;
      ret = chdir(args.c_str());
      if(ret == -1) 
      {
      	perror("Change directory error");
      	return true;
      }
      else 
      	return true;
    }
    //for pushd command
    if(command == string("pushd"))
    {
      paths.push(args);
      int ret;
      ret = chdir(args.c_str());
      if(ret == -1) 
      {
      	perror("Change directory error");
      	return true;
      }
      else 
      	return true;
    }
    //for popd command
    if(command == string("popd")){
      if(paths.empty())
      {
      	perror("Empth path stack");
      	return true;
      }
      const char * tmp = (paths.top()).c_str();
      int ret;
      ret = chdir(tmp);
      if(ret == -1) 
      {
      	perror("Change directory error");
      	return true;
      }
      else
      {
      	paths.pop();
      	return true;
      }
    }
    //for dirstack command
    if(command == string("dirstack"))
    {
      stack<string> disp(paths);
      for (size_t i = 0;i < disp.size();++i)
      {
      		cout << disp.top() << endl;
      		disp.pop();
      }
      return true;;
    }
    return false;

}
