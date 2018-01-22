#pragma once
#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

#include <map>
#include <deque>
#include <string>

#include "DataViewController.h"

class Shape;

class File
{
private:
   std::string fileName;
   std::string pathDirectory;
   std::map<int,Shape*> shapes;

   DataViewController viewController;

   bool saved;
public:
   ~File();
   File(std::string _fileName);

   int generateIdShape();

   std::deque<Shape*> getShapes();
   void addShapeOnFile(Shape* newShape);

   std::string getFileName();
   void setFileName(std::string name);

   std::string getPath();
   void setPath(std::string path);

   bool isSaved();
   bool alreadySaved();
   void setSaved(bool status);

   std::map<int,std::deque<Point>> repaintAll();
   std::map<int,std::deque<Point>> repaintRectInPresentation();

   DataViewController& getDataViewController();
};

#endif // INCLUDED_FILE_H