#include "File.h"
#include "Shape.h"

File::~File()
{
   for (int i= 0; i < shapes.size() ; ++i)
      delete shapes[i];
   shapes.clear();
}

File::File(std::string _fileName,int _width,int _height)
{
   saved= false;
   width= _width;
   height= _height;
   fileName= _fileName;
}

///////////////////////////////////////////////////////////////////////////////

int File::generateIdShape()
{
   return shapes.size();
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Shape*> File::getShapes()
{
   std::deque<Shape*> dequeShapes;
   std::map<int,Shape*>::iterator iter;
   for (iter= shapes.begin() ; iter != shapes.end() ; ++iter)
      dequeShapes.push_back(iter->second);
   return dequeShapes;
}

void File::addShapeOnFile(Shape* newShape)
{
   saved= false;
   shapes.insert(std::pair<int,Shape*>(newShape->getId(),newShape));
}