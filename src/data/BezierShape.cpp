#include "BezierShape.h"
#include "Point.h"

BezierShape::BezierShape(Point* _initial,Point* _control,Point* _final) 
{
   initial= _initial;
   control= _control;
   final= _final;
}

BezierShape::~BezierShape()
{
   delete initial;
   delete control;
   delete final;
}

///////////////////////////////////////////////////////////////////////////////

int BezierShape::getId()
{
   return SHAPE_ID::BEZIER;
}

std::deque<Point*> BezierShape::getPoints()
{
   std::deque<Point*> points;
   points.push_back(initial);
   points.push_back(control);
   points.push_back(final);
   return points;
}