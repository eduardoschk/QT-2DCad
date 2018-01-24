#include "IOFile.h"
#include <fstream>
#include <sstream>

#include "File.h"
#include "Shape.h"
#include "Coordinate.h"
#include "ArcShape.h"
#include "LineShape.h"
#include "BezierShape.h"

bool IOFile::save(File& file)
{
   std::stringstream ss;
   ss << file.getPath() << "/" << file.getFileName();

   std::ofstream stream;
   stream.open(ss.str(),std::ios_base::binary | std::ios_base::ate | std::ios_base::trunc);

   save(stream,file);

   stream.close();
   return true;
}

void IOFile::saveAs(std::string completedPath,File& file)
{
   std::ofstream stream;
   stream.open(completedPath,std::ios_base::binary | std::ios_base::ate | std::ios_base::trunc);

   save(stream,file);

   stream.close();
}

void IOFile::save(std::ofstream& stream,File& file)
{
   std::deque<Shape*> shapes= file.getShapes();
   int countShapes= (int)shapes.size();

   stream.write((char*)&countShapes,sizeof(int));

   for (int i= 0; i < countShapes ; ++i)
      writeShape(stream,*shapes[i]);
   stream.flush();
}

File* IOFile::open(std::string pathAndFile)
{
   std::ifstream stream;
   stream.open(pathAndFile);
   stream.seekg(0);

   int countShapes;

   stream.read((char*)&countShapes,sizeof(int));

   File* file= new File("");

   for (int i= 0 ; i < countShapes ; ++i)
      file->addShapeOnFile(readShape(file->generateIdShape(),stream));

   return file;
}

///////////////////////////////////////////////////////////////////////////////

void IOFile::writeShape(std::ofstream& stream,Shape& shape)
{
   int type= shape.getType();
   
   std::deque<Coordinate> CoordinatesOfShape= shape.getSelectedCoordinates();

   stream.write((char*)&type,sizeof(int));

   for (int i= 0 ; i < CoordinatesOfShape.size() ; ++i)
      writeCoordinate(stream,CoordinatesOfShape[i]);
}

void IOFile::writeCoordinate(std::ofstream& stream,Coordinate coordinate)
{
   stream.write((char*)&coordinate.x,sizeof(int));
   stream.write((char*)&coordinate.y,sizeof(int));
}

///////////////////////////////////////////////////////////////////////////////

Shape* IOFile::readShape(int id,std::ifstream& stream)
{
   int shapeType;
   stream.read((char*)&shapeType,sizeof(int));

   switch (shapeType) {
      case SHAPE_TYPE::LINE:   return readLineShape(id,stream);
      case SHAPE_TYPE::BEZIER: return readBezierShape(id,stream);
      case SHAPE_TYPE::ARC:    return readArcShape(id,stream);
   }
   return nullptr;
}

Coordinate IOFile::readCoordinate(std::ifstream& stream)
{
   Coordinate p= Coordinate();
   stream.read((char*)&p.x,sizeof(int));
   stream.read((char*)&p.y,sizeof(int));
   return p;
}

Shape* IOFile::readArcShape(int id,std::ifstream& stream)
{
   Coordinate center= readCoordinate(stream);
   Coordinate initial= readCoordinate(stream);
   Coordinate final= readCoordinate(stream);

   return new ArcShape(id,center,initial,final);
}

Shape* IOFile::readLineShape(int id,std::ifstream& stream)
{
   Coordinate initial= readCoordinate(stream);
   Coordinate final= readCoordinate(stream);

   return new LineShape(id,initial,final);
}

Shape* IOFile::readBezierShape(int id,std::ifstream& stream)
{
   Coordinate initial= readCoordinate(stream);
   Coordinate control= readCoordinate(stream);
   Coordinate final= readCoordinate(stream);

   return new BezierShape(id,initial,control,final);
}
