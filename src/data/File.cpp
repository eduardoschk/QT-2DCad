 #include "File.h"
#include "Shape.h"
#include "Point.h"
#include "Rect.h"

File::~File()
{
   for (int i= 0; i < shapes.size() ; ++i)
      delete shapes[i];
   shapes.clear();
}

File::File(std::string _fileName) : viewController()
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
   for (std::pair<int,Shape*> shape : shapes) 
      dequeShapes.push_back(shape.second);
   return dequeShapes;
}

void File::addShapeOnFile(Shape* newShape)
{
   saved= false;
   viewController.newShape(newShape->getOriginalRectShape());
   shapes.insert(std::pair<int,Shape*>(newShape->getId(),newShape));
}

///////////////////////////////////////////////////////////////////////////////

std::map<int,std::deque<Point>> File::repaintAll()
{
   std::map<int,std::deque<Point>> points;
   for (std::pair<int,Shape*> shape : shapes) 
      points.insert(std::pair<int,std::deque<Point>>(shape.second->getId(),shape.second->getPointsToDraw(viewController)));
   return points;
}

std::map<int,std::deque<Point>> File::repaintRectInPresentation()
{
   std::map<int,std::deque<Point>> points;
   for (std::pair<int,Shape*> shape : shapes) {
      std::deque<Point> pointsOfShape= shape.second->getPointsToDrawInRect(viewController);
      points.insert(std::pair<int,std::deque<Point>>(shape.second->getId(),pointsOfShape));
   }
   return points;
}

///////////////////////////////////////////////////////////////////////////////

std::string File::getFileName() 
{ 
   return fileName; 
}

void File::setFileName(std::string name) 
{ 
   fileName= name; 
}

///////////////////////////////////////////////////////////////////////////////

std::string File::getPath() 
{ 
   return pathDirectory; 
}

void File::setPath(std::string path) 
{ 
   pathDirectory= path; 
}

///////////////////////////////////////////////////////////////////////////////

bool File::isSaved()
{
   return saved;
}

bool File::alreadySaved()
{ 
   return pathDirectory.size() > 0; 
}

void File::setSaved(bool status) 
{ 
   saved= status; 
}

///////////////////////////////////////////////////////////////////////////////

DataViewController& File::getDataViewController()
{
   return viewController;
}