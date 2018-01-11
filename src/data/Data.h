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

   bool hasFile() { return currentFile; }

   void setCurrentFile(File* file);
   File& getCurrentFile() { return *currentFile; }
};

#endif // INCLUDED_DATA_H