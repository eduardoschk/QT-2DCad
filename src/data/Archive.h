#pragma once
#ifndef INCLUDED_ARCHIVE_H
#define INCLUDED_ARCHIVE_H

#include <deque>
#include <string>

class Shape;
class Point;

class Archive
{
private:
    std::string archiveName;
    std::deque<Shape*> shapes;

    int width;
    int height;

    Shape* readLineShape( std::ifstream & stream);
    Shape* readArcShape( std::ifstream & stream );
    Shape* readBezierShape( std::ifstream & stream );
    Point* readPoint( std::ifstream & stream );

public:
    Archive(std::string _archiveName, int _width, int _height);
    Archive() {}
    ~Archive() {}

    void save( std::string path );
    Archive* open( std::string pathAndFile );

    void setArchiveName( std::string name );
    std::string getArchiveName();

    void setWidth( int _width);
    int getWidth();

    void setHeight( int _height );
    int getHeight();

    void addShapeOnArchive( Shape * newShape );
    std::deque<Shape*> getShapes();
};

#endif // INCLUDED_ARCHIVE_H