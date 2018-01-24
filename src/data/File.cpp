 #include "File.h"
#include "Shape.h"
#include "Coordinate.h"
#include "Rect.h"

File::~File()
{
   for (int i= 0; i < shapes.size() ; ++i)
      delete shapes[i];
   shapes.clear();
}

File::File(std::string _fileName)
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
   viewController.newShape(newShape->getRectShape());
   shapes.insert(std::pair<int,Shape*>(newShape->getId(),newShape));
}

///////////////////////////////////////////////////////////////////////////////

std::map<int,std::deque<Coordinate>> File::repaintAll()
{
   std::map<int,std::deque<Coordinate>> coordinates;
   for (std::pair<int,Shape*> shape : shapes) 
      coordinates.insert(std::pair<int,std::deque<Coordinate>>(shape.second->getId(),shape.second->getCoordinatesToDraw(viewController)));
   return coordinates;
}

std::map<int,std::deque<Coordinate>> File::repaintRectInPresentation()
{
   std::map<int,std::deque<Coordinate>> coordinates;
   for (std::pair<int,Shape*> shape : shapes) {
      Rect rectShape= shape.second->getCurrentRectShape(viewController);
      if (viewController.rectIsInPresentation(rectShape)) {
         std::deque<Coordinate> coordinatesOfShape= shape.second->getCoordinatesToDrawInRect(viewController);
         coordinates.insert(std::pair<int,std::deque<Coordinate>>(shape.second->getId(),coordinatesOfShape));
      }
      else
         coordinates.insert(std::pair<int,std::deque<Coordinate>>(shape.second->getId(),0));
   }
   return coordinates;
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