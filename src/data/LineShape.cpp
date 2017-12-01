#include "LineShape.h"
#include "Point.h"

LineShape::LineShape(int _id,Point* _initial,Point* _final) : Shape(_id)
{
   initial= _initial;
   final= _final;
}

LineShape::~LineShape() {}

///////////////////////////////////////////////////////////////////////////////

int LineShape::getType()
{
   return SHAPE_TYPE::LINE;
}

std::deque<Point*> LineShape::getPoints()
{
   std::deque<Point*> points;
   points.push_back(initial);
   points.push_back(final);
   return points;
}
