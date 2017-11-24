#pragma once 
#ifndef INCLUDED_DATA_H
#define INCLUDED_DATA_H

#include <string>
#include <deque>
#include "ShapeTypes.h"
#include "Point.h"

class File;

class Data {
private:
   File* currentFile;
   SHAPE_TYPE::TYPE currentTypeShape;
   std::deque<Point> actualPoints;

public:
   ~Data();
   Data();

   bool save();
   void saveAs(std::string completedPath);
   File* open(std::string pathAndFile);

   bool hasFile() { return currentFile; }

   File& getCurrentFile() { return *currentFile; }
   void setCurrentFile(File* file);

   void setShapeType(SHAPE_TYPE::TYPE type) { currentTypeShape= type; }
   SHAPE_TYPE::TYPE getSelectShapeType() { return currentTypeShape; }

   void addPoint(Point point) { actualPoints.push_back(point); }
   std::deque<Point> getPoints() { return actualPoints; }
   void resetPoints() { actualPoints.clear(); }
};

#endif // INCLUDED_DATA_H