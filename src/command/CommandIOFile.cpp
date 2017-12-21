#include "CommandIOFile.h"

FileParams CommandIOFile::dividerNameOfPath(std::string completedPath)
{
   int indexOf= 0;
   for (int i= 0 ; i < completedPath.size() ; ++i) {
      if (completedPath.at(i) == '/' )
         indexOf= i;
   }
   FileParams file;
   file.path=  completedPath.substr(0,indexOf);
   file.name= completedPath.substr(indexOf + 1,completedPath.size());
   return file;
}
