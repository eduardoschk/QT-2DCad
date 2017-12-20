#include "LineShape.h"
#include "Point.h"

LineShape::LineShape(int _id,Point _initial,Point _final) : Shape(_id)
{
   final= _final;
   initial= _initial;
}

///////////////////////////////////////////////////////////////////////////////

int LineShape::getType()
{
   return SHAPE_TYPE::LINE;
}

std::deque<Point> LineShape::getPoints()
{
   std::deque<Point> points;
   points.push_back(initial);
   points.push_back(final);
   return points;
}
