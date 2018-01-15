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

std::deque<Point> LineShape::getPointsToDraw(float scale)
{
   std::deque<Point> points;
   int x= initial.x;
   int y= initial.y;

   int distanceY = final.y - initial.y;
   int distanceX = final.x - initial.x;
   int stepX,stepY;

   distanceY < 0 ? stepY= -1 : stepY= 1;
   distanceY *= stepY;

   distanceX < 0 ? stepX= -1 : stepX= 1;
   distanceX *= stepX;

   if (distanceX > distanceY) {
      for (int fraction= distanceY - distanceX ; x != final.x ; points.push_back(Point(x,y)*scale)) {
         if (fraction >= 0) {
            y += stepY;
            fraction -= distanceX;
         }
         x += stepX;
         fraction += distanceY;
      }
   }
   else {
      for (int fraction = distanceX - distanceY ; y != final.y ; points.push_back(Point(x,y)*scale)) {
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

std::deque<Point> LineShape::getPointsToDrawInRect(float scale,Rect rect)
{
   std::deque<Point> pointInRect;
   std::deque<Point> allPoints= getPointsToDraw(scale);

   for (Point point : allPoints) {
      if (point.on(rect))
         pointInRect.push_back(point-Point(rect.initialX,rect.initialY));
   }
   return pointInRect;
}

std::deque<Point> LineShape::getSelectedPoints()
{
   std::deque<Point> points;
   points.push_back(initial);
   points.push_back(final);
   return points;
}
