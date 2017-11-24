#include "LineShape.h"
#include "Point.h"

LineShape::LineShape(Point* _initial,Point* _final)
{
   initial= _initial;
   final= _final;
}

LineShape::~LineShape()
{
   delete final;
   delete initial;
}

///////////////////////////////////////////////////////////////////////////////

int LineShape::getId()
{
   return SHAPE_ID::LINE;
}

std::deque<Point*> LineShape::getPoints()
{
   std::deque<Point*> points;
   points.push_back(initial);
   points.push_back(final);
   return points;
}
