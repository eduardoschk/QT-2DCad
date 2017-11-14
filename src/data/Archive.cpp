#include "Archive.h"
#include "Shape.h"
#include "LineShape.h"
#include <fstream>
#include <iostream>

Archive::Archive( std::string _archiveName ) : archiveName(_archiveName)  {}

Archive::~Archive() {}

void Archive::addShapeOnArchive( Shape * newShape )
{
    shapes.push_back( newShape );
}

char finalShape = '\n';

void Archive::save( std::string path )
{
    std::ofstream stream;
    stream.open( path.append("/").append(archiveName).append(".tois") );

    for ( int i= 0; i < shapes.size() ; ++i ) {
        int id= shapes[i]->getId();   
        stream.write( ( char* ) &id , sizeof( int ) );

        std::deque<Shape::Point> pointsOfShape = shapes[i]->getPoints();
        int size = pointsOfShape.size();
        stream.write( ( char* ) &size , sizeof( int ) );

        for ( int s= 0 ; s < pointsOfShape.size() ; ++s ) {
            stream.write( ( char* ) &pointsOfShape[s].x , sizeof( int ) );
            stream.write( ( char* ) &pointsOfShape[s].y , sizeof( int ) );
        }
        stream.flush();

        stream.write( ( char* ) &finalShape , sizeof( char ) );
    }
    stream.close();
}

Archive * Archive::open( std::string pathAndFile)
{
    std::ifstream stream;
    stream.open( pathAndFile);
    stream.seekg(0);

    Shape * shape;

    for ( int i= 0; i < shapes.size() ; ++i ) {
        int id;
        stream.read( ( char* ) &id , sizeof( int ) );

        shape = new LineShape();

        int size;
        stream.read( ( char* ) &size , sizeof( int ) );

        for ( int s= 0 ; s < size ; ++s ) {
            int x , y;
            stream.read( ( char* ) &x , sizeof( int ) );
            stream.read( ( char* ) &y , sizeof( int ) );
        }

        char final = ' ';
        while ( final != '\n' )
            stream.read( ( char* ) &final , sizeof( char ) );
    }
    return nullptr;
}
