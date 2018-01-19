 #include "File.h"
#include "Shape.h"
#include "Point.h"
#include "Rect.h"

#include <memory>

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

std::deque<Shape*>& File::getShapes()
{
   std::shared_ptr<std::deque<Shape*>> dequeShapes(new std::deque<Shape*>);
   for (std::pair<int,Shape*> shape : shapes) {
      dequeShapes.get()->push_back(shape.second);
   }
   return *dequeShapes.get();
}

void File::addShapeOnFile(Shape* newShape)
{
   saved= false;
   viewController.newShape(newShape->getOriginalRectShape());
   shapes.insert(std::pair<int,Shape*>(newShape->getId(),newShape));
}

///////////////////////////////////////////////////////////////////////////////

std::map<int,std::deque<Point>>& File::repaintAll()
{
   std::shared_ptr<std::map<int,std::deque<Point>>> points(new std::map<int,std::deque<Point>>);
   for (std::pair<int,Shape*> shape : shapes) 
      points.get()->insert(std::pair<int,std::deque<Point>>(shape.second->getId(),shape.second->getPointsToDraw(viewController)));
   return *points.get();
}

std::map<int,std::deque<Point>>& File::repaintRectInPresentation()
{
   std::shared_ptr<std::map<int,std::deque<Point>>> points(new std::map<int,std::deque<Point>>);
   for (std::pair<int,Shape*> shape : shapes) {

      shape.second->getCurrentRectShape(viewController).partiallyContained(viewController.getRectPresentation());

      std::deque<Point> pointsOfShape= shape.second->getPointsToDrawInRect(viewController);

      points.get()->insert(std::pair<int,std::deque<Point>>(shape.second->getId(),pointsOfShape));
   }
   return *points.get();
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