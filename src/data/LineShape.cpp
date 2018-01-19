#include "LineShape.h"
#include "Rect.h"
#include "DataViewController.h"

LineShape::LineShape(int _id,Point& _initial,Point& _final) : Shape(_id),originalFinalPoint(_final), originalInitialPoint(_initial) {}

///////////////////////////////////////////////////////////////////////////////

int LineShape::getType()
{
   return SHAPE_TYPE::LINE;
}

///////////////////////////////////////////////////////////////////////////////

Rect LineShape::calcRectShape(float scale)
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

Rect LineShape::getOriginalRectShape()
{
   currentFinalPoint= originalFinalPoint;
   currentInitialPoint= originalInitialPoint;
   return calcRectShape(1);
}

Rect LineShape::getCurrentRectShape(DataViewController& dataViewController)
{
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);

   return calcRectShape(dataViewController.getScale());
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Point> LineShape::calcPointsToDraw(float scale)
{
   std::deque<Point> points;
   
   int x= currentInitialPoint.x;
   int y= currentInitialPoint.y;

   int distanceY = currentFinalPoint.y - currentInitialPoint.y;
   int distanceX = currentFinalPoint.x - currentInitialPoint.x;
   int stepX,stepY;

   distanceY < 0 ? stepY= -1 : stepY= 1;
   distanceY *= stepY;

   distanceX < 0 ? stepX= -1 : stepX= 1;
   distanceX *= stepX;

   if (distanceX > distanceY) {
      for (int fraction= distanceY - distanceX ; x != currentFinalPoint.x ; points.push_back(Point(x,y))) {
         if (fraction >= 0) {
            y += stepY;
            fraction -= distanceX;
         }
         x += stepX;
         fraction += distanceY;
      }
   }
   else {
      for (int fraction = distanceX - distanceY ; y != currentFinalPoint.y ; points.push_back(Point(x,y))) {
         if (fraction >= 0) {
            x += stepX;
            fraction -= distanceY;
         }
         y += stepY;
         fraction += distanceX;
      }
   }
   return points;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Point> LineShape::getPointsToDraw(DataViewController& dataViewController)
{
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);

   return calcPointsToDraw(dataViewController.getScale());
}

std::deque<Point> LineShape::getPointsToDrawInRect(DataViewController& dataViewController)
{
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);

   std::deque<Point> fixsPoints;

   for (Point point : calcPointsToDraw(dataViewController.getScale())) {
      if (point.on(dataViewController.getRectPresentation()))
         fixsPoints.push_back(dataViewController.fixPoint(point));
   }

   return fixsPoints;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Point> LineShape::getSelectedPoints()
{
   std::deque<Point> points;
  
   points.push_back(originalInitialPoint);
   points.push_back(originalFinalPoint);
   return points;
}
