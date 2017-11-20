#include "File.h"
#include "Shape.h"
#include "Point.h"
#include "LineShape.h"
#include "BezierShape.h"
#include "ArcShape.h"
#include <fstream>
#include <iostream>
#include <sstream>

char initFile = '\n';
char finalShape = '\n';

File::~File()
{
   for ( int i= 0; i < shapes.size() ; ++i )
      delete shapes[i];
   shapes.clear();
}

File::File( std::string _fileName , int _width , int _height ) : 
    fileName(_fileName), width(_width), height(_height), saved(false) {}

///////////////////////////////////////////////////////////////////////////////

void File::save( std::ofstream & stream )
{
   int countShapes= shapes.size();

   stream.write( ( char* ) &initFile , sizeof( char ) );
   stream.write( ( char* ) &width , sizeof( int ) );
   stream.write( ( char* ) &height , sizeof( int ) );
   stream.write( ( char* ) &countShapes , sizeof( int ) );

   for ( int i= 0; i < countShapes ; ++i )
      writeShape( stream , *shapes[i] );
   stream.flush();
}

void File::save()
{
   std::stringstream ss;
   ss << pathDirectory << "/" << fileName;

   std::ofstream stream;
   stream.open( ss.str() , std::ios_base::binary | std::ios_base::ate | std::ios_base::trunc );

   save( stream );

   saved= true;
   stream.close();
}

void File::saveAs( std::string completedPath )
{
   std::ofstream stream;
   stream.open( completedPath , std::ios_base::binary | std::ios_base::ate | std::ios_base::trunc );

   save( stream );

   stream.close();
}

void File::writeShape( std::ofstream & stream , Shape & shape )
{
   int id= shape.getId();
   stream.write( ( char* ) &id , sizeof( int ) );

   std::deque<Point*> pointsOfShape = shape.getPoints();
   int size = pointsOfShape.size();
   stream.write( ( char* ) &size , sizeof( int ) );

   for ( int i= 0 ; i < pointsOfShape.size() ; ++i ) 
      writePoint( stream , *pointsOfShape[i] );

   stream.write( ( char* ) &finalShape , sizeof( char ) );
}

void File::writePoint( std::ofstream & stream , Point & point )
{
   stream.write( ( char* ) &point.x , sizeof( int ) );
   stream.write( ( char* ) &point.y , sizeof( int ) );
}

///////////////////////////////////////////////////////////////////////////////

File * File::open( std::string pathFile)
{
   std::ifstream stream;
   stream.open( pathFile );
   stream.seekg(0);

   File * file = new File();
   int _initFile, _width, _height, _countShapes;

   stream.read( ( char* ) &_initFile , sizeof( char ) );
   stream.read( ( char* ) &_width , sizeof( int ) );
   stream.read( ( char* ) &_height , sizeof( int ) );
   stream.read( ( char* ) &_countShapes , sizeof( int ) );

   file->setWidth( _width );
   file->setHeight( _height );

   for ( int i= 0; i < _countShapes ; ++i )
      file->addShapeOnFile( readShape(stream) );

   return file;
}

Shape* File::readShape( std::ifstream & stream )
{
   int idShape;
   stream.read( ( char* ) &idShape , sizeof( int ) );
   switch ( idShape )
   {
   case LINE:   return readLineShape( stream );
   case BEZIER: return readBezierShape( stream );
   case ARC:    return readArcShape( stream );
   }
}

Shape* File::readLineShape( std::ifstream & stream )
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

Shape* File::readArcShape( std::ifstream & stream )
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

Shape* File::readBezierShape( std::ifstream & stream )
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

Point* File::readPoint( std::ifstream & stream )
{
   Point * p= new Point();
   stream.read( ( char* ) &p->x , sizeof( int ) );
   stream.read( ( char* ) &p->y , sizeof( int ) );
   return p;
}

///////////////////////////////////////////////////////////////////////////////

std::string File::getFileName()
{
   return fileName;
}

void File::setFileName( std::string name )
{
   fileName= name;
}

std::string File::getPath()
{
   return pathDirectory;
}

void File::setPath( std::string path )
{
   pathDirectory= path;
}

void File::setWidth( int _width )
{
   width= _width;
}

int File::getWidth() 
{
   return width;
}

void File::setHeight( int _height )
{
   height= _height;
}

int File::getHeight()
{
   return height;
}

void File::addShapeOnFile( Shape * newShape )
{
   saved= false;
   shapes.push_back( newShape );
}

std::deque<Shape*> File::getShapes()
{
   return shapes;
}