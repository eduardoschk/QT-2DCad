#pragma once
#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

#include <map>
#include <deque>
#include <string>
#include "Point.h"
#include "ShapeTypes.h"
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
   File(std::string _fileName,Size sizeShape);

   int generateIdShape();

   std::deque<Shape*> getShapes();
   void addShapeOnFile(Shape* newShape);

   std::string getFileName() { return fileName; }
   void setFileName(std::string name) { fileName= name; }

   std::string getPath() { return pathDirectory; }
   void setPath(std::string path) { pathDirectory= path; }

   bool isSaved() { return saved; }
   void setSaved(bool status) { saved= status; }
   bool alreadySaved() { return pathDirectory.size() > 0; }

   std::map<int,std::deque<Point>> repaintAll();
   std::map<int,std::deque<Point>> repaintRect(Rect rect);

   DataViewController& getDataViewController() { return viewController; }
};

#endif // INCLUDED_FILE_H