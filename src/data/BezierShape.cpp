#include <Math.h>

#include "BezierShape.h"
#include "Rect.h"
#include "DataViewController.h"

BezierShape::BezierShape(int _id,Coordinate& _initial,Coordinate& _control,Coordinate& _final) : Shape(_id)
{
   originalFinalCoordinate= _final;
   originalInitialCoordinate= _initial;
   originalControlCoordinate= _control;
   calcRectShape();
}

///////////////////////////////////////////////////////////////////////////////

Coordinate BezierShape::calcCoordinate(float distance)
{
   return Coordinate(calcX(distance),calcY(distance));
}

float BezierShape::calcX(float distance)
{
   return pow((1 - distance),2) * currentInitialCoordinate.x + 2 * distance * (1 - distance) * currentControlCoordinate.x + pow(distance,2) * currentFinalCoordinate.x;
}

float BezierShape::calcY(float distance)
{
   return pow((1 - distance),2) * currentInitialCoordinate.y + 2 * distance * (1 - distance) * currentControlCoordinate.y + pow(distance,2) * currentFinalCoordinate.y;
}

///////////////////////////////////////////////////////////////////////////////

int BezierShape::getType()
{
   return SHAPE_TYPE::BEZIER;
}

///////////////////////////////////////////////////////////////////////////////

void BezierShape::calcRectShape()
{
   currentFinalCoordinate= originalFinalCoordinate;
   currentInitialCoordinate= originalInitialCoordinate;
   currentControlCoordinate= originalControlCoordinate;

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

Rect BezierShape::getRectShape()
{
   return rectShape;
}

Rect BezierShape::getCurrentRectShape(DataViewController& dataViewController)
{
   Coordinate repairedInitialCoordinate= dataViewController.repairCoordinateWorldToView(rectShape.getInitialCordinate());
   return Rect(repairedInitialCoordinate,rectShape.width * dataViewController.getScale(),rectShape.height * dataViewController.getScale());
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> BezierShape::getSelectedCoordinates()
{
   std::deque<Coordinate> coordinates;

   coordinates.push_back(originalInitialCoordinate);
   coordinates.push_back(originalControlCoordinate);
   coordinates.push_back(originalFinalCoordinate);
   return coordinates;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> BezierShape::calcCoordinatesOfShape(float scale)
{
   std::deque<Coordinate> CoordinatesToDraw;
   for (float distance= 0; distance <= 1; distance+= 0.01f / scale)
      CoordinatesToDraw.push_back(calcCoordinate(distance));
   CoordinatesToDraw.push_back(calcCoordinate(1));
   return CoordinatesToDraw;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> BezierShape::getCoordinatesToDraw(DataViewController& dataViewController)
{
   currentInitialCoordinate= dataViewController.repairCoordinateWorldToView(originalInitialCoordinate);
   currentControlCoordinate= dataViewController.repairCoordinateWorldToView(originalControlCoordinate);
   currentFinalCoordinate= dataViewController.repairCoordinateWorldToView(originalFinalCoordinate);

   return calcCoordinatesOfShape(dataViewController.getScale());
}

std::deque<Coordinate> BezierShape::getCoordinatesToDrawInRect(DataViewController& dataViewController)
{
   currentInitialCoordinate= dataViewController.repairCoordinateWorldToView(originalInitialCoordinate);
   currentControlCoordinate= dataViewController.repairCoordinateWorldToView(originalControlCoordinate);
   currentFinalCoordinate= dataViewController.repairCoordinateWorldToView(originalFinalCoordinate);

   std::deque<Coordinate> repairedCoordinates;

   for (Coordinate coordinate : calcCoordinatesOfShape(dataViewController.getScale())) {
      if (coordinate.on(dataViewController.getRectPresentation()))
         repairedCoordinates.push_back(dataViewController.discardScroll(coordinate));
   }

   return repairedCoordinates;
}
