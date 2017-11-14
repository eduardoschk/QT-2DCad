#pragma once
#ifndef INCLUDED_ARCHIVE_H
#define INCLUDED_ARCHIVE_H

#include <deque>
#include <string>

class Shape;

class Archive
{
private:
    std::string archiveName;
    std::deque<Shape*> shapes;

public:
    Archive(std::string _archiveName);
    ~Archive();

    void addShapeOnArchive( Shape * newShape );
    void save( std::string path );

    Archive* open( std::string pathAndFile );
};

#endif // INCLUDED_ARCHIVE_H