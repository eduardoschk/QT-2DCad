#include "ArcShape.h"
#include "Rect.h"
#include "DataViewController.h"

#define PI 3.14159265

ArcShape::~ArcShape() {}

ArcShape::ArcShape(int _id,Coordinate& _center,Coordinate& _initial,Coordinate& _final) : Shape(_id)
{
   originalFinalCoordinate= _final;
   originalCenterCoordinate= _center;
   originalInitialCoordinate= _initial;
   calcRectShape();
}

///////////////////////////////////////////////////////////////////////////////

int ArcShape::getType()
{
   return SHAPE_TYPE::ARC;
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::calcRectShape()
{
   currentFinalCoordinate= originalFinalCoordinate;
   currentCenterCoordinate= originalCenterCoordinate;
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

Rect ArcShape::getRectShape()
{
   return rectShape;
}

Rect ArcShape::getCurrentRectShape(DataViewController& dataViewController)
{
   Coordinate repairedInitialCoordinate= dataViewController.repairCoordinateWorldToView(rectShape.getInitialCordinate());
   return Rect(repairedInitialCoordinate,rectShape.width * dataViewController.getScale(), rectShape.height * dataViewController.getScale());
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> ArcShape::getSelectedCoordinates()
{
   std::deque<Coordinate> coordinates;

   coordinates.push_back(originalCenterCoordinate);
   coordinates.push_back(originalInitialCoordinate);
   coordinates.push_back(originalFinalCoordinate);

   return coordinates;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> ArcShape::calcCoordinatesOfShape(float scale)
{
   radius= calcPythagoras(currentCenterCoordinate,currentInitialCoordinate);

   std::deque<Coordinate> coordinates;
   double distanceBetweenInitAndFinal= calcPythagoras(currentCenterCoordinate,currentFinalCoordinate);
   switch (calcQuadrantCoordinate(currentInitialCoordinate)) {
      case UM:       calcCoordinatesWithInitialCoordinateInFirstQuadrant(coordinates,distanceBetweenInitAndFinal,scale);     break;
      case DOIS:     calcCoordinatesWithInitialCoordinateInSecondQuadrant(coordinates,distanceBetweenInitAndFinal,scale);    break;
      case TRES:     calcCoordinatesWithInitialCoordinateInThirdQuadrant(coordinates,distanceBetweenInitAndFinal,scale);     break;
      case QUATRO:   calcCoordinatesWithInitialCoordinateInFourthQuadrant(coordinates,distanceBetweenInitAndFinal,scale);    break;
   }
   return coordinates;
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Coordinate> ArcShape::getCoordinatesToDraw(DataViewController& dataViewController)
{
   currentInitialCoordinate= dataViewController.repairCoordinateWorldToView(originalInitialCoordinate);
   currentCenterCoordinate= dataViewController.repairCoordinateWorldToView(originalCenterCoordinate);
   currentFinalCoordinate= dataViewController.repairCoordinateWorldToView(originalFinalCoordinate);

   return calcCoordinatesOfShape(dataViewController.getScale());
}

std::deque<Coordinate> ArcShape::getCoordinatesToDrawInRect(DataViewController& dataViewController)
{
   currentInitialCoordinate= dataViewController.repairCoordinateWorldToView(originalInitialCoordinate);
   currentCenterCoordinate= dataViewController.repairCoordinateWorldToView(originalCenterCoordinate);
   currentFinalCoordinate= dataViewController.repairCoordinateWorldToView(originalFinalCoordinate);

   std::deque<Coordinate> repairedCoordinates;

   for (Coordinate coordinate : calcCoordinatesOfShape(dataViewController.getScale())) {
      if (coordinate.on(dataViewController.getRectPresentation()))
         repairedCoordinates.push_back(dataViewController.discardScroll(coordinate));
   }

   return repairedCoordinates;
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::addCoordinates(std::deque<Coordinate>& coordinates,const double initAngule,const double finalAngule,float scale)
{
   for (double ang= fmod(initAngule,361.0f) ; ang >= fmod(finalAngule,360); ang-= 0.5f / scale)
     coordinates.push_back(calcCoordinateOnAngle(ang));
}

///////////////////////////////////////////////////////////////////////////////

Coordinate ArcShape::calcCoordinateOnAngle(double angle)
{
   double y= radius * (sin(angle * PI / 180));
   double x= radius * (cos(angle * PI / 180));

   return Coordinate(currentCenterCoordinate.x + x,currentCenterCoordinate.y - y);
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::calcCoordinatesWithInitialCoordinateInFirstQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantCoordinate(currentFinalCoordinate)) {
      case UM:
      {
         double angInit= calcAngle(diffCordenates(currentCenterCoordinate.y,currentInitialCoordinate.y),radius);
         double angFinal= calcAngle(diffCordenates(currentCenterCoordinate.y,currentFinalCoordinate.y),distanceInitFinal);
         if (angInit > angFinal) {
            prevAngle= calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
            nextAngle= calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

            addCoordinates(coordinates,90 - prevAngle,nextAngle,scale);
         }
         else {
            prevAngle= calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
            nextAngle= calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

            addCoordinates(coordinates,90 - nextAngle,prevAngle,scale);
         }
      }
      break;
      case DOIS:
      prevAngle= calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
      nextAngle= calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,180 - nextAngle,prevAngle,scale);

      break;
      case TRES:
      prevAngle= calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
      nextAngle= calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

      addCoordinates(coordinates,270 - nextAngle,prevAngle,scale);

      break;
      case QUATRO:
      prevAngle= calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
      nextAngle= calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,360 - nextAngle,prevAngle,scale);

      break;
   }
}

void ArcShape::calcCoordinatesWithInitialCoordinateInSecondQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantCoordinate(currentFinalCoordinate)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,180 - prevAngle,nextAngle,scale);

      break;
      case DOIS:
      {
         double angInit = calcAngle(diffCordenates(currentCenterCoordinate.y,currentInitialCoordinate.y),radius);
         double angFinal = calcAngle(diffCordenates(currentCenterCoordinate.y,currentFinalCoordinate.y),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
            nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

            addCoordinates(coordinates,180 - prevAngle,90 + nextAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
            nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

            addCoordinates(coordinates,180 - nextAngle,90 + prevAngle,scale);
         }
      }
      break;
      case TRES:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

      addCoordinates(coordinates,270 - nextAngle,90 + prevAngle,scale);

      break;
      case QUATRO:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,360 - nextAngle,90 + prevAngle,scale);

      break;
   }
}

void ArcShape::calcCoordinatesWithInitialCoordinateInThirdQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantCoordinate(currentFinalCoordinate)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,270 - prevAngle,nextAngle,scale);

      break;
      case DOIS:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

      addCoordinates(coordinates,270 - prevAngle,90 + nextAngle,scale);

      break;
      case TRES:
      {
         double angInit = calcAngle(diffCordenates(currentCenterCoordinate.y,currentInitialCoordinate.y),radius);
         double angFinal = calcAngle(diffCordenates(currentCenterCoordinate.y,currentFinalCoordinate.y),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
            nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

            addCoordinates(coordinates,270 - nextAngle,180 + prevAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
            nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

            addCoordinates(coordinates,270 - prevAngle,180 + nextAngle,scale);
         }
      }
      break;
      case QUATRO:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,360 - nextAngle,180 + prevAngle,scale);
      break;
   }
}

void ArcShape::calcCoordinatesWithInitialCoordinateInFourthQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantCoordinate(currentFinalCoordinate)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

      addCoordinates(coordinates,90 - nextAngle,0,scale);
      addCoordinates(coordinates,360,270 + prevAngle,scale);

      break;
      case DOIS:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

      addCoordinates(coordinates,180 - nextAngle,0,scale);
      addCoordinates(coordinates,360,270 + prevAngle,scale);

      break;
      case TRES:
      prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
      nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

      addCoordinates(coordinates,270 - nextAngle,0,scale);
      addCoordinates(coordinates,360,270 + prevAngle,scale);

      break;
      case QUATRO:
      {
         double angInit = calcAngle(diffCordenates(currentCenterCoordinate.y,currentInitialCoordinate.y),radius);
         double angFinal = calcAngle(diffCordenates(currentCenterCoordinate.y,currentFinalCoordinate.y),distanceInitFinal);

         if (angInit > angFinal) {
            prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.x,currentCenterCoordinate.x),radius);
            nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.y,currentCenterCoordinate.y),distanceInitFinal);

            addCoordinates(coordinates,360 - nextAngle,270 + prevAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(currentInitialCoordinate.y,currentCenterCoordinate.y),radius);
            nextAngle = calcAngle(diffCordenates(currentFinalCoordinate.x,currentCenterCoordinate.x),distanceInitFinal);

            addCoordinates(coordinates,360 - prevAngle,270 + nextAngle,scale);
         }
      }
      break;
   }
}

///////////////////////////////////////////////////////////////////////////////

int ArcShape::diffCordenates(const int coord1,const int coord2)
{
   return (coord1 > coord2) ? (coord1 - coord2) : (coord2 - coord1);
}

QUADRANT ArcShape::calcQuadrantCoordinate(const Coordinate& coordinate)
{
   if (coordinate.x > currentCenterCoordinate.x) {
      if (coordinate.y > currentCenterCoordinate.y)
         return QUATRO;
      else 
         return UM;
   }
   else {
      if (coordinate.y > currentCenterCoordinate.y)
         return TRES; 
      else 
         return DOIS;
   }
}

///////////////////////////////////////////////////////////////////////////////

double ArcShape::calcAngle(double oppositeLeg,double hypotenuse)
{
   return asin(oppositeLeg / hypotenuse) * 180 / PI;
}

double ArcShape::calcPythagoras(const Coordinate& coord1,const Coordinate& coord2)
{
   int x = diffCordenates(coord1.x,coord2.x);
   int y = diffCordenates(coord1.y,coord2.y);
   return sqrt(pow(x,2) + pow(y,2));
}
