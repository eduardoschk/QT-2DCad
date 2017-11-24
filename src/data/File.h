#pragma once
#ifndef INCLUDED_ARCHIVE_H
#define INCLUDED_ARCHIVE_H

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
   std::deque<Shape*> shapes;

   int width;
   int height;

   bool saved;

public:
   File() : saved(false) {}
   File(std::string _fileName,int _width,int _height);
   ~File();

   std::string getFileName() { return fileName; }
   void setFileName(std::string name) { fileName= name; }

   bool alreadySaved() { return pathDirectory.size() > 0; }
   std::string getPath() { return pathDirectory; }
   void setPath(std::string path) { pathDirectory= path; }

   int getWidth() { return width; }
   void setWidth(int _width) { width= _width; }

   int getHeight() { return height; }
   void setHeight(int _height) { height= _height; }

   std::deque<Shape*> getShapes() { return shapes; }
   void addShapeOnFile(Shape* newShape);

   void setSaved(bool status) { saved= status; }
   bool isSaved() { return saved; }
};

#endif // INCLUDED_ARCHIVE_H