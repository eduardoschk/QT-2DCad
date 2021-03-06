#include "Data.h"

#include "File.h"
#include "IOFile.h"

Data::~Data() 
{
   if (currentFile)
      delete currentFile;
}

Data::Data()
{
   currentFile= nullptr;
}

///////////////////////////////////////////////////////////////////////////////

void Data::setCurrentFile(File* file)
{
   if (currentFile)
      delete currentFile;
   currentFile= file;
}

///////////////////////////////////////////////////////////////////////////////

bool Data::save()
{
   currentFile->setSaved(IOFile().save(*currentFile));
   return currentFile->isSaved();
}

void Data::saveAs(std::string completedPath)
{
   return IOFile().saveAs(completedPath, *currentFile);
}

File* Data::open(std::string pathAndFile)
{
   return IOFile().open(pathAndFile);
}

///////////////////////////////////////////////////////////////////////////////

bool Data::hasFile() 
{ 
   return currentFile; 
}

File& Data::getCurrentFile()
{
   return *currentFile;
}