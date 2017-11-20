#pragma once
#ifndef INCLUDED_ARCHIVE_H
#define INCLUDED_ARCHIVE_H

#include <deque>
#include <string>

class Shape;
class Point;

class File
{
private:
   std::string fileName;
   std::string pathDirectory;
   std::deque<Shape*> shapes;

   int width;
   int height;

   bool saved;

   void writeShape( std::ofstream & stream, Shape & shape );
   void writePoint( std::ofstream & stream, Point & point );

   Shape* readShape( std::ifstream & stream );
   Point* readPoint( std::ifstream & stream );
   Shape* readArcShape( std::ifstream & stream );
   Shape* readLineShape( std::ifstream & stream );
   Shape* readBezierShape( std::ifstream & stream );

   void save( std::ofstream & stream);

public:
   File() : saved(false) {}
   File(std::string _fileName, int _width, int _height);
   ~File();

   void save();
   void saveAs( std::string completedPath );
   File* open( std::string pathAndFile );

   std::string getFileName();
   void setFileName( std::string name );

   std::string getPath();
   void setPath( std::string path );

   int getWidth();
   void setWidth( int _width );

   int getHeight();
   void setHeight( int _height );

   std::deque<Shape*> getShapes();
   void addShapeOnFile( Shape * newShape );

   bool isSaved() { return saved; }
};

#endif // INCLUDED_ARCHIVE_H