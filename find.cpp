#include "find.h"
//find the file in the directory
bool findFile(string filename,string dir)
{
	int isFind = 0;
	char b[1000];
	strcpy(b,filename.c_str());
	struct dirent *pDirEntry = NULL;
    DIR          *pDir      = NULL;
    const char *directory = dir.c_str();
    if( (pDir = opendir(directory)) == NULL )
    {
        return false;
    }
    else
    {
        while( (pDirEntry = readdir(pDir)) )
        {
          	if(strcmp(b,pDirEntry->d_name) == 0)
            {
            	isFind = 1;
            	break;
            }
        }
        closedir(pDir);
              
    } 
    if(isFind == 1)
    {
    	return true;;
    }
    else
   	{
   		return false;
   	}

}
