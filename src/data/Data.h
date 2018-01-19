#pragma once 
#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

#include <string>
#include <deque>

class File;

class Data {
private:
   File* currentFile;

public:
   ~Data();
   Data();

   bool save();
   void saveAs(std::string completedPath);
   File* open(std::string pathAndFile);

   bool hasFile();

   File& getCurrentFile();
   void setCurrentFile(File* file);
};

#endif // INCLUDED_DATA_H