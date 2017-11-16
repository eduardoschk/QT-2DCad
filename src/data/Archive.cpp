#include "Archive.h"
#include "Shape.h"
#include "Point.h"
#include "LineShape.h"
#include "BezierShape.h"
#include "ArcShape.h"
#include <fstream>
#include <iostream>

char initArchive = '\n';
char finalShape = '\n';

Archive::Archive( std::string _archiveName , int _width , int _height ) : 
    archiveName(_archiveName), width(_width), height(_height)  {}

///////////////////////////////////////////////////////////////////////////////

void Archive::save( std::string path )
{
    std::ofstream stream;
    stream.open( path.append("/").append(archiveName).append(".tois") );
    int countShapes= shapes.size();

    stream.write( ( char* ) &initArchive , sizeof( char ) );
    stream.write( ( char* ) &width , sizeof( int ) );
    stream.write( ( char* ) &height , sizeof( int ) );
    stream.write( ( char* ) &countShapes , sizeof( int ) );

    for ( int i= 0; i < countShapes ; ++i ) {
        int id= shapes[i]->getId();   
        stream.write( ( char* ) &id , sizeof( int ) );

        std::deque<Point*> pointsOfShape = shapes[i]->getPoints();
        int size = pointsOfShape.size();
        stream.write( ( char* ) &size , sizeof( int ) );

        for ( int s= 0 ; s < pointsOfShape.size() ; ++s ) {
            stream.write( ( char* ) &pointsOfShape[s]->x , sizeof( int ) );
            stream.write( ( char* ) &pointsOfShape[s]->y , sizeof( int ) );
        }
        stream.flush();

        stream.write( ( char* ) &finalShape , sizeof( char ) );
    }
    stream.close();
}

Archive * Archive::open( std::string pathFile)
{
    std::ifstream stream;
    stream.open( pathFile);
    stream.seekg(0);

    Archive * archive = new Archive();
    int _initArchive, _width, _height, _countShapes;

    stream.read( ( char* ) &_initArchive , sizeof( char ) );
    stream.read( ( char* ) &_width , sizeof( int ) );
    stream.read( ( char* ) &_height , sizeof( int ) );
    stream.read( ( char* ) &_countShapes , sizeof( int ) );

    archive->setArchiveName( pathFile );
    archive->setWidth( _width );
    archive->setHeight( _height );

    for ( int i= 0; i < _countShapes ; ++i ) {
        int idShape;
        stream.read( ( char* ) &idShape , sizeof( int ) );
        switch ( idShape )
        {
        case LINE:   archive->addShapeOnArchive( readLineShape( stream ) );     break;
        case BEZIER: archive->addShapeOnArchive( readBezierShape( stream ) );   break;
        case ARC:    archive->addShapeOnArchive( readArcShape( stream ) );      break;
        }
    }

    return archive;
}

Shape* Archive::readLineShape( std::ifstream & stream )
{
    LineShape * line= new LineShape();
    int size;
    stream.read( ( char* ) &size , sizeof( int ) );

    line->setInitial( readPoint( stream ) );
    line->setFinal( readPoint( stream ) );

    char final = ' ';
    while ( final != finalShape )
        stream.read( ( char* ) &final , sizeof( char ) );
    return line;
}

Shape* Archive::readArcShape( std::ifstream & stream )
{
    ArcShape * arc= new ArcShape();
    int size;
    stream.read( ( char* ) &size , sizeof( int ) );

    arc->setCenter( readPoint( stream ) );
    arc->setInitial( readPoint( stream ) );
    arc->setFinal( readPoint( stream ) );

    char final = ' ';
    while ( final != finalShape )
        stream.read( ( char* ) &final , sizeof( char ) );
    return arc;
}

Shape* Archive::readBezierShape( std::ifstream & stream )
{
    BezierShape * bezier= new BezierShape();
    int size;
    stream.read( ( char* ) &size , sizeof( int ) );

    bezier->setInitial( readPoint( stream ) );
    bezier->setControl( readPoint( stream ) );
    bezier->setFinal( readPoint( stream ) );

    char final = ' ';
    while ( final != finalShape )
        stream.read( ( char* ) &final , sizeof( char ) );
    return bezier;
}

Point* Archive::readPoint( std::ifstream & stream )
{
    Point * p= new Point();
    stream.read( ( char* ) &p->x , sizeof( int ) );
    stream.read( ( char* ) &p->y , sizeof( int ) );
    return p;
}

///////////////////////////////////////////////////////////////////////////////

void Archive::setArchiveName( std::string name )
{
    archiveName= name;
}

std::string Archive::getArchiveName()
{
    return archiveName;
}

void Archive::setWidth( int _width )
{
    width= _width;
}

int Archive::getWidth() 
{
    return width;
}

void Archive::setHeight( int _height )
{
    height= _height;
}

int Archive::getHeight()
{
    return height;
}

void Archive::addShapeOnArchive( Shape * newShape )
{
    shapes.push_back( newShape );
}

std::deque<Shape*> Archive::getShapes()
{
    return shapes;
}