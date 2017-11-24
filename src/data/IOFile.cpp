#include "IOFile.h"
#include <fstream>
#include <sstream>

#include "File.h"
#include "Shape.h"
#include "Point.h"
#include "ArcShape.h"
#include "LineShape.h"
#include "BezierShape.h"

char initFile = '\n';
char finalShape = '\n';

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
   int countShapes= (int)file.getShapes().size();
   int width= file.getWidth();
   int height= file.getHeight();

   stream.write((char*)&initFile,sizeof(char));
   stream.write((char*)&width,sizeof(int));
   stream.write((char*)&height,sizeof(int));
   stream.write((char*)&countShapes,sizeof(int));

   for (int i= 0; i < countShapes ; ++i)
      writeShape(stream,*file.getShapes()[i]);
   stream.flush();
}

File* IOFile::open(std::string pathAndFile)
{
   std::ifstream stream;
   stream.open(pathAndFile);
   stream.seekg(0);

   File* file= new File();
   int _initFile,_width,_height,_countShapes;

   stream.read((char*)&_initFile,sizeof(char));
   stream.read((char*)&_width,sizeof(int));
   stream.read((char*)&_height,sizeof(int));
   stream.read((char*)&_countShapes,sizeof(int));

   file->setWidth(_width);
   file->setHeight(_height);

   for (int i= 0 ; i < _countShapes ; ++i)
      file->addShapeOnFile(readShape(stream));

   return file;
}

///////////////////////////////////////////////////////////////////////////////

void IOFile::writeShape(std::ofstream& stream,Shape& shape)
{
   int id= shape.getId();
   stream.write((char*)&id,sizeof(int));

   std::deque<Point*> pointsOfShape = shape.getPoints();
   int size= (int)pointsOfShape.size();
   stream.write((char*)&size,sizeof(int));

   for (int i= 0 ; i < pointsOfShape.size() ; ++i)
      writePoint(stream,*pointsOfShape[i]);

   stream.write((char*)&finalShape,sizeof(char));
}

void IOFile::writePoint(std::ofstream& stream,Point& point)
{
   stream.write((char*)&point.x,sizeof(int));
   stream.write((char*)&point.y,sizeof(int));
}

///////////////////////////////////////////////////////////////////////////////

Shape* IOFile::readShape(std::ifstream& stream)
{
   int idShape;
   stream.read((char*)&idShape,sizeof(int));
   switch (idShape) {
      case SHAPE_ID::LINE:   return readLineShape(stream);
      case SHAPE_ID::BEZIER: return readBezierShape(stream);
      case SHAPE_ID::ARC:    return readArcShape(stream);
   }
}

Point* IOFile::readPoint(std::ifstream& stream)
{
   Point * p= new Point();
   stream.read((char*)&p->x,sizeof(int));
   stream.read((char*)&p->y,sizeof(int));
   return p;
}

Shape* IOFile::readArcShape(std::ifstream& stream)
{
   int size;
   stream.read((char*)&size,sizeof(int));

   Point* center= readPoint(stream);
   Point* initial= readPoint(stream);
   Point* final= readPoint(stream);

   ArcShape* arc= new ArcShape(center,initial,final);

   char finalChar= ' ';
   while (finalChar != finalShape)
      stream.read((char*)&finalChar,sizeof(char));
   return arc;
}

Shape* IOFile::readLineShape(std::ifstream& stream)
{
   int size;
   stream.read((char*)&size,sizeof(int));

   Point* initial= readPoint(stream);
   Point* final= readPoint(stream);

   LineShape* line= new LineShape(initial,final);

   char finalChar= ' ';
   while (finalChar != finalShape)
      stream.read((char*)&finalChar,sizeof(char));
   return line;
}

Shape* IOFile::readBezierShape(std::ifstream& stream)
{
   int size;
   stream.read((char*)&size,sizeof(int));

   Point* initial= readPoint(stream);
   Point* control= readPoint(stream);
   Point* final= readPoint(stream);

   BezierShape* bezier= new BezierShape(initial,control,final);

   char finalChar= ' ';
   while (finalChar != finalShape)
      stream.read((char*)&finalChar,sizeof(char));
   return bezier;
}
