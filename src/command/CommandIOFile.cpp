#include "CommandIOFile.h"

FileParams CommandIOFile::getNameAndFolderPathOfAbsolutePath(std::string completedPath)
{
   int indexOfBar= 0;
   for (int i= 0 ; i < completedPath.size() ; ++i) {
      if (completedPath.at(i) == '/' )
         indexOfBar= i;
   }
   FileParams file;
   file.path= completedPath.substr(0,indexOfBar);
   file.name= completedPath.substr(indexOfBar + 1,completedPath.size());
   return file;
}
