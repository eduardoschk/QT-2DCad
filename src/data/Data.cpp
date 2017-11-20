#include "Data.h"

Data::Data() : currentFile(nullptr) {}
Data::~Data() 
{
   if ( currentFile )
      delete currentFile;
}

File & Data::getCurrentFile()
{
   return *currentFile;
}

void Data::setCurrentFile( File * archive )
{
   if ( currentFile )
      delete currentFile;
   currentFile= archive;
}