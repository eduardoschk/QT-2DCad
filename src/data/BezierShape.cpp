#include "BezierShape.h"
#include <Math.h>

BezierShape::BezierShape(int _id,Point _initial,Point _control,Point _final) : Shape(_id)
{
   initial= _initial;
   control= _control;
   final= _final;
}

///////////////////////////////////////////////////////////////////////////////

Point BezierShape::calcPoint(float distance)
{
   return Point(calcX(distance),calcY(distance));
}

float BezierShape::calcX(float distance)
{
   return pow((1 - distance),2) * initial.x + 2 * distance * (1 - distance) * control.x + pow(distance,2) * final.x;
}

float BezierShape::calcY(float distance)
{
   return pow((1 - distance),2) * initial.y + 2 * distance * (1 - distance) * control.y + pow(distance,2) * final.y;
}

///////////////////////////////////////////////////////////////////////////////

int BezierShape::getType()
{
   return SHAPE_TYPE::BEZIER;
}

std::deque<Point> BezierShape::getPointsToDraw(float scale)
{
   std::deque<Point> pointsToDraw;
   for (float distance= 0; distance <= 1; distance+= 0.05f)
      pointsToDraw.push_back(calcPoint(distance)*scale);
   pointsToDraw.push_back(calcPoint(1)*scale);
   return pointsToDraw;
}

std::deque<Point> BezierShape::getSelectedPoints()
{
   std::deque<Point> points;
   points.push_back(initial);
   points.push_back(control);
   points.push_back(final);
   return points;
}