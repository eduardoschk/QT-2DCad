#include "ArcShape.h"
#include "Point.h"

ArcShape::~ArcShape()
{
   delete final;
   delete center;
   delete initial;
}

ArcShape::ArcShape(int _id,Point* _center,Point* _initial,Point* _final) : Shape(_id)
{
   final= _final;
   center= _center;
   initial= _initial;
}

///////////////////////////////////////////////////////////////////////////////

int ArcShape::getType()
{
   return SHAPE_TYPE::ARC;
}

std::deque<Point*> ArcShape::getPoints()
{
   std::deque<Point*> points;
   points.push_back(center);
   points.push_back(initial);
   points.push_back(final);
   return points;
}