#include "IOFile.h"
#include <fstream>
#include <sstream>

#include "File.h"
#include "Shape.h"
#include "Point.h"
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
   
   std::deque<Point> pointsOfShape= shape.getSelectedPoints();

   stream.write((char*)&type,sizeof(int));

   for (int i= 0 ; i < pointsOfShape.size() ; ++i)
      writePoint(stream,pointsOfShape[i]);
}

void IOFile::writePoint(std::ofstream& stream,Point point)
{
   stream.write((char*)&point.x,sizeof(int));
   stream.write((char*)&point.y,sizeof(int));
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

Point IOFile::readPoint(std::ifstream& stream)
{
   Point p= Point();
   stream.read((char*)&p.x,sizeof(int));
   stream.read((char*)&p.y,sizeof(int));
   return p;
}

Shape* IOFile::readArcShape(int id,std::ifstream& stream)
{
   Point center= readPoint(stream);
   Point initial= readPoint(stream);
   Point final= readPoint(stream);

   return new ArcShape(id,center,initial,final);
}

Shape* IOFile::readLineShape(int id,std::ifstream& stream)
{
   Point initial= readPoint(stream);
   Point final= readPoint(stream);

   return new LineShape(id,initial,final);
}

Shape* IOFile::readBezierShape(int id,std::ifstream& stream)
{
   Point initial= readPoint(stream);
   Point control= readPoint(stream);
   Point final= readPoint(stream);

   return new BezierShape(id,initial,control,final);
}
