 #include "File.h"
#include "Shape.h"

File::~File()
{
   for (int i= 0; i < shapes.size() ; ++i)
      delete shapes[i];
   shapes.clear();
}

File::File(std::string _fileName,Size sizeShape) : viewController(sizeShape)
{
   saved= false;
   fileName= _fileName;
}

///////////////////////////////////////////////////////////////////////////////

int File::generateIdShape()
{
   return (int)shapes.size();
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

///////////////////////////////////////////////////////////////////////////////

std::map<int,std::deque<Point>> File::repaintAll()
{
   std::map<int,std::deque<Point>> points;
   for (std::pair<int,Shape*> shape : shapes) {
      points.insert(std::pair<int,std::deque<Point>>(shape.second->getId(),shape.second->getPointsToDraw(viewController.getZoomScale())));
   }
   return points;
}

std::map<int,std::deque<Point>> File::repaintRect(Rect rect)
{
   return std::map<int,std::deque<Point>>();
}
