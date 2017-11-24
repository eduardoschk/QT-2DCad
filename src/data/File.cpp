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

void File::addShapeOnFile(Shape * newShape)
{
   saved= false;
   shapes.push_back(newShape);
}