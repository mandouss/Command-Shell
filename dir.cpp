#include "dir.h"
//function dealing with the directories command
bool changeDir(string command,string args,stack<string>& path)
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
      char cwd[PATH_MAX+1];
      getcwd(cwd,PATH_MAX+1);
      string old_path(cwd);
      path.push(old_path);
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
    if(path.empty())
      {
	perror("Empth path stack");
	return true;
      }
    const char * tmp = path.top().c_str();
    //cout<<tmp<<endl;
    int ret;
    ret = chdir(tmp);
    if(ret == -1) 
      {
	perror("Change directory error");
	return true;
      }
    else
      {
	path.pop();
	return true;
      }
  }
  
  
  //for dirstack command
  if(command == string("dirstack"))
    {
      if(path.size() == 0)
	{
	  cout<<"nothing in the path"<<endl;
	  return true;
	}
      stack<string> disp(path);
      stack<string> reverse;
      for (size_t i = 0;i < path.size();++i)
	{
	  reverse.push(disp.top());
	  disp.pop();
	}
      for (size_t i = 0;i < path.size();++i)
	{
	  cout<<reverse.top()<<endl;
	  reverse.pop();
	}
      
      return true;
    }
  return false;
  
}
