#include "BezierShape.h"
#include "Point.h"

BezierShape::~BezierShape()
{
   delete final;
   delete initial;
   delete control;
}

BezierShape::BezierShape(int _id,Point* _initial,Point* _control,Point* _final) : Shape(_id)
{
   initial= _initial;
   control= _control;
   final= _final;
}

///////////////////////////////////////////////////////////////////////////////

int BezierShape::getType()
{
   return SHAPE_TYPE::BEZIER;
}

std::deque<Point> BezierShape::getPoints()
{
   std::deque<Point> points;
   //points.push_back(initial);
   //points.push_back(control);
   //points.push_back(final);
   return points;
}