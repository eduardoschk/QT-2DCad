#include "ArcShape.h"
#include "Point.h"

ArcShape::ArcShape(Point* _center,Point* _initial,Point* _final)
{
   final= _final;
   center= _center;
   initial= _initial;
}

ArcShape::~ArcShape()
{
   delete final;
   delete center;
   delete initial;
}

///////////////////////////////////////////////////////////////////////////////

int ArcShape::getId()
{
   return SHAPE_ID::ARC;
}

std::deque<Point*> ArcShape::getPoints()
{
   std::deque<Point*> points;
   points.push_back(center);
   points.push_back(initial);
   points.push_back(final);
   return points;
}