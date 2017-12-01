#pragma once
#ifndef INCLUDED_ARCHIVE_H
#define INCLUDED_ARCHIVE_H

#include <map>
#include <deque>
#include <string>
#include "Point.h"
#include "ShapeTypes.h"

class Shape;

class File
{
private:
   std::string fileName;
   std::string pathDirectory;
   std::map<int,Shape*> shapes;

   int width;
   int height;

   bool saved;

public:
   ~File();
   File() : saved(false) {}
   File(std::string _fileName,int _width,int _height);

   int generateIdShape();

   std::deque<Shape*> getShapes();
   void addShapeOnFile(Shape* newShape);

   std::string getFileName() { return fileName; }
   void setFileName(std::string name) { fileName= name; }

   std::string getPath() { return pathDirectory; }
   void setPath(std::string path) { pathDirectory= path; }

   int getWidth() { return width; }
   void setWidth(int _width) { width= _width; }

   int getHeight() { return height; }
   void setHeight(int _height) { height= _height; }

   bool isSaved() { return saved; }
   void setSaved(bool status) { saved= status; }
   bool alreadySaved() { return pathDirectory.size() > 0; }
};

#endif // INCLUDED_ARCHIVE_H