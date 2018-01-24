#include "LineShape.h"
#include "Rect.h"
#include "DataViewController.h"

LineShape::LineShape(int _id,Coordinate& _initial,Coordinate& _final) : Shape(_id)
{
   originalFinalCoordinate= _final;
   originalInitialCoordinate= _initial;
   calcRectShape();
}

///////////////////////////////////////////////////////////////////////////////

int LineShape::getType()
{
   return SHAPE_TYPE::LINE;
}

///////////////////////////////////////////////////////////////////////////////

void LineShape::calcRectShape()
{
   currentFinalCoordinate= originalFinalCoordinate;
   currentInitialCoordinate= originalInitialCoordinate;

   int east,north,west,south;
   west= south= 0;
   east= north= 99999;

   for (Coordinate coordinate : calcCoordinatesOfShape(1)) {
      if (coordinate.x < east)
         east= coordinate.x;
      if (coordinate.x > west)
         west= coordinate.x;
      if (coordinate.y < north)
         north= coordinate.y;
      if (coordinate.y > south)
         south= coordinate.y;
   }

   rectShape= Rect(east,north,(west - east),(south - north));
}

///////////////////////////////////////////////////////////////////////////////

Rect LineShape::getRectShape()
{
   return rectShape;
}

Rect LineShape::getCurrentRectShape(DataViewController& dataViewController)
{
   Coordinate repairedInitialCoordinate= dataViewController.repairCoordinateWorldToView(rectShape.getInitialCordinate());
   float repairedWidth,repairedHeight;
   repairedWidth= rectShape.width * dataViewController.getScale();
   repairedHeight= rectShape.height * dataViewController.getScale();
   return Rect(repairedInitialCoordinate, repairedWidth, repairedHeight);
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> LineShape::getSelectedCoordinates()
{
   std::deque<Coordinate> coordinates;

   coordinates.push_back(originalInitialCoordinate);
   coordinates.push_back(originalFinalCoordinate);
   return coordinates;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> LineShape::calcCoordinatesOfShape(float scale)
{
   std::deque<Coordinate> coordinates;
   
   int x= currentInitialCoordinate.x;
   int y= currentInitialCoordinate.y;

   int distanceY = currentFinalCoordinate.y - currentInitialCoordinate.y;
   int distanceX = currentFinalCoordinate.x - currentInitialCoordinate.x;
   int stepX,stepY;

   distanceY < 0 ? stepY= -1 : stepY= 1;
   distanceY *= stepY;

   distanceX < 0 ? stepX= -1 : stepX= 1;
   distanceX *= stepX;

   if (distanceX > distanceY) {
      for (int fraction= distanceY - distanceX ; x != currentFinalCoordinate.x ; coordinates.push_back(Coordinate(x,y))) {
         if (fraction >= 0) {
            y += stepY;
            fraction -= distanceX;
         }
         x += stepX;
         fraction += distanceY;
      }
   }
   else {
      for (int fraction = distanceX - distanceY ; y != currentFinalCoordinate.y ; coordinates.push_back(Coordinate(x,y))) {
         if (fraction >= 0) {
            x += stepX;
            fraction -= distanceY;
         }
         y += stepY;
         fraction += distanceX;
      }
   }

   return coordinates;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> LineShape::getCoordinatesToDraw(DataViewController& dataViewController)
{
   currentFinalCoordinate= dataViewController.repairCoordinateWorldToView(originalFinalCoordinate);
   currentInitialCoordinate= dataViewController.repairCoordinateWorldToView(originalInitialCoordinate);

   return calcCoordinatesOfShape(dataViewController.getScale());
}

std::deque<Coordinate> LineShape::getCoordinatesToDrawInRect(DataViewController& dataViewController)
{
   currentFinalCoordinate= dataViewController.repairCoordinateWorldToView(originalFinalCoordinate);
   currentInitialCoordinate= dataViewController.repairCoordinateWorldToView(originalInitialCoordinate);

   std::deque<Coordinate> repairedCoordinates;
   for (Coordinate coordinate : calcCoordinatesOfShape(dataViewController.getScale())) {
      if (coordinate.on(dataViewController.getRectPresentation()))
         repairedCoordinates.push_back(dataViewController.discardScroll(coordinate));
   }
   return repairedCoordinates;
}
