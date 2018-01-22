#include <Math.h>

#include "BezierShape.h"
#include "Rect.h"
#include "DataViewController.h"

BezierShape::BezierShape(int _id,Point& _initial,Point& _control,Point& _final) : Shape(_id)
{
   originalInitialPoint= _initial;
   originalControlPoint= _control;
   originalFinalPoint= _final;
}

///////////////////////////////////////////////////////////////////////////////

Point BezierShape::calcPoint(float distance)
{
   return Point(calcX(distance),calcY(distance));
}

float BezierShape::calcX(float distance)
{
   return pow((1 - distance),2) * currentInitialPoint.x + 2 * distance * (1 - distance) * currentControlPoint.x + pow(distance,2) * currentFinalPoint.x;
}

float BezierShape::calcY(float distance)
{
   return pow((1 - distance),2) * currentInitialPoint.y + 2 * distance * (1 - distance) * currentControlPoint.y + pow(distance,2) * currentFinalPoint.y;
}

///////////////////////////////////////////////////////////////////////////////

int BezierShape::getType()
{
   return SHAPE_TYPE::BEZIER;
}

///////////////////////////////////////////////////////////////////////////////

Rect BezierShape::calcRectShape(float scale)
{
   int east,north,west,south;
   west= south= 0;
   east= north= 99999;

   for (Point point : calcPointsToDraw(scale)) {
      if (point.x < east)
         east= point.x;
      if (point.x > west)
         west= point.x;
      if (point.y < north)
         north= point.y;
      if (point.y > south)
         south= point.y;
   }

   return Rect(east,north,(west - east),(south - north));
}

Rect BezierShape::getOriginalRectShape()
{
   currentFinalPoint= originalFinalPoint;
   currentControlPoint= originalControlPoint;
   currentInitialPoint= originalInitialPoint;

   return calcRectShape(1);
}

Rect BezierShape::getCurrentRectShape(DataViewController& dataViewController)
{
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);
   currentControlPoint= dataViewController.fixPointWorldInView(originalControlPoint);
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);

   return calcRectShape(dataViewController.getScale());
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Point> BezierShape::calcPointsToDraw(float scale)
{
   std::deque<Point> pointsToDraw;
   for (float distance= 0; distance <= 1; distance+= 0.01f / scale)
      pointsToDraw.push_back(calcPoint(distance));
   pointsToDraw.push_back(calcPoint(1));
   return pointsToDraw;
}

std::deque<Point> BezierShape::getPointsToDraw(DataViewController& dataViewController)
{
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);
   currentControlPoint= dataViewController.fixPointWorldInView(originalControlPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);

   return calcPointsToDraw(dataViewController.getScale());
}

std::deque<Point> BezierShape::getPointsToDrawInRect(DataViewController& dataViewController)
{
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);
   currentControlPoint= dataViewController.fixPointWorldInView(originalControlPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);

   std::deque<Point> fixsPoints;

   for (Point point : calcPointsToDraw(dataViewController.getScale())) {
      if (point.on(dataViewController.getRectPresentation()))
         fixsPoints.push_back(dataViewController.discardScroll(point));
   }

   return fixsPoints;
}

std::deque<Point> BezierShape::getSelectedPoints()
{
   std::deque<Point> points;

   points.push_back(originalInitialPoint);
   points.push_back(originalControlPoint);
   points.push_back(originalFinalPoint);
   return points;
}