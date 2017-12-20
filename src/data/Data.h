#pragma once 
#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

#include <string>
#include <deque>

#include "Point.h"
#include "ShapeTypes.h"
#include "DataViewController.h"

class File;

class Data {
private:
   File* currentFile;
   DataViewController viewController;

public:
   ~Data();
   Data();

   bool save();
   void saveAs(std::string completedPath);
   File* open(std::string pathAndFile);

   bool hasFile() { return currentFile; }

   void setCurrentFile(File* file);
   File& getCurrentFile() { return *currentFile; }

   DataViewController& getDataViewController() { return viewController; }
};

#endif // INCLUDED_DATA_H