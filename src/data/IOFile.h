#pragma once
#ifndef INCLUDED_IO_FILE_H
#define INCLUDED_IO_FILE_H

#include <string>
class File;
class Shape;
class Point;

class IOFile
{
private:
   void writeShape(std::ofstream& stream,Shape& shape);
   void writePoint(std::ofstream& stream,Point& point);

   Shape* readShape(std::ifstream& stream);
   Point* readPoint(std::ifstream& stream);
   Shape* readArcShape(std::ifstream& stream);
   Shape* readLineShape(std::ifstream& stream);
   Shape* readBezierShape(std::ifstream& stream);

   void save(std::ofstream& stream,File& file);
public:
   ~IOFile() {}
   IOFile() {}

   bool save(File& file);
   void saveAs(std::string completedPath,File& file);
   File* open(std::string pathAndFile);

};

#endif // INCLUDED_IO_FILE_H