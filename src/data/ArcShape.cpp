#include "ArcShape.h"
#include "Rect.h"
#include "DataViewController.h"

#define PI 3.14159265

ArcShape::~ArcShape()
{
}

ArcShape::ArcShape(int _id,Point& _center,Point& _initial,Point& _final) : Shape(_id),originalFinalPoint(_final), originalCenterPoint(_center), originalInitialPoint(_initial) {}

///////////////////////////////////////////////////////////////////////////////

int ArcShape::getType()
{
   return SHAPE_TYPE::ARC;
}

///////////////////////////////////////////////////////////////////////////////

Rect ArcShape::calcRectShape(float scale)
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

Rect ArcShape::getOriginalRectShape()
{
   currentCenterPoint= originalCenterPoint;
   currentFinalPoint= originalFinalPoint;
   currentInitialPoint= originalInitialPoint;

   return calcRectShape(1);
}

Rect ArcShape::getCurrentRectShape(DataViewController& dataViewController)
{
   currentCenterPoint= dataViewController.fixPointWorldInView(originalCenterPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);

   return calcRectShape(dataViewController.getScale());
}

///////////////////////////////////////////////////////////////////////////////

std::deque<Point> ArcShape::calcPointsToDraw(float scale)
{
   raio= calcPitagoras(currentCenterPoint,currentInitialPoint);

   std::deque<Point> points;
   switch (calcQuadrantPoint(currentInitialPoint)) {
      case UM:       drawWithInitialPointInFirstQuadrant(points,calcPitagoras(currentCenterPoint,currentFinalPoint),scale);     break;
      case DOIS:     drawWithInitialPointInSecondQuadrant(points,calcPitagoras(currentCenterPoint,currentFinalPoint),scale);    break;
      case TRES:     drawWithInitialPointInThirdQuadrant(points,calcPitagoras(currentCenterPoint,currentFinalPoint),scale);     break;
      case QUATRO:   drawWithInitialPointInFourthQuadrant(points,calcPitagoras(currentCenterPoint,currentFinalPoint),scale);    break;
   }
   return points;
}

std::deque<Point> ArcShape::getPointsToDraw(DataViewController& dataViewController)
{
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);
   currentCenterPoint= dataViewController.fixPointWorldInView(originalCenterPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);

   return calcPointsToDraw(dataViewController.getScale());
}

std::deque<Point> ArcShape::getPointsToDrawInRect(DataViewController& dataViewController)
{
   currentInitialPoint= dataViewController.fixPointWorldInView(originalInitialPoint);
   currentCenterPoint= dataViewController.fixPointWorldInView(originalCenterPoint);
   currentFinalPoint= dataViewController.fixPointWorldInView(originalFinalPoint);

   std::deque<Point> fixsPoints;

   for (Point point : calcPointsToDraw(dataViewController.getScale())) {
      if (point.on(dataViewController.getRectPresentation()))
         fixsPoints.push_back(dataViewController.fixPoint(point));
   }

   return fixsPoints;
}

std::deque<Point> ArcShape::getSelectedPoints()
{
   std::deque<Point> points;

   points.push_back(originalCenterPoint);
   points.push_back(originalInitialPoint);
   points.push_back(originalFinalPoint);

   return points;
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::drawPoints(std::deque<Point>& points,const double initAngule,const double finalAngule,float scale)
{
   for (double ang= fmod(initAngule,361.0f) ; ang >= fmod(finalAngule,360); ang-= 0.5f / scale)
     points.push_back(calcPointOnAngle(ang));
}

///////////////////////////////////////////////////////////////////////////////

Point ArcShape::calcPointOnAngle(double angle)
{
   double y= raio * (sin(angle * PI / 180));
   double x= raio * (cos(angle * PI / 180));

   return Point(currentCenterPoint.x + x,currentCenterPoint.y - y);
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::drawWithInitialPointInFirstQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(currentFinalPoint)) {
      case UM:
      {
         double angInit= calcAngle(diffCordenates(currentCenterPoint.y,currentInitialPoint.y),raio);
         double angFinal= calcAngle(diffCordenates(currentCenterPoint.y,currentFinalPoint.y),distanceInitFinal);
         if (angInit > angFinal) {
            prevAngle= calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
            nextAngle= calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

            drawPoints(points,90 - prevAngle,nextAngle,scale);
         }
         else {
            prevAngle= calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
            nextAngle= calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

            drawPoints(points,90 - nextAngle,prevAngle,scale);
         }
      }
      break;
      case DOIS:
      prevAngle= calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
      nextAngle= calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,180 - nextAngle,prevAngle,scale);

      break;
      case TRES:
      prevAngle= calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
      nextAngle= calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

      drawPoints(points,270 - nextAngle,prevAngle,scale);

      break;
      case QUATRO:
      prevAngle= calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
      nextAngle= calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,360 - nextAngle,prevAngle,scale);

      break;
   }
}

void ArcShape::drawWithInitialPointInSecondQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(currentFinalPoint)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,180 - prevAngle,nextAngle,scale);

      break;
      case DOIS:
      {
         double angInit = calcAngle(diffCordenates(currentCenterPoint.y,currentInitialPoint.y),raio);
         double angFinal = calcAngle(diffCordenates(currentCenterPoint.y,currentFinalPoint.y),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
            nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

            drawPoints(points,180 - prevAngle,90 + nextAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
            nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

            drawPoints(points,180 - nextAngle,90 + prevAngle,scale);
         }
      }
      break;
      case TRES:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

      drawPoints(points,270 - nextAngle,90 + prevAngle,scale);

      break;
      case QUATRO:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,360 - nextAngle,90 + prevAngle,scale);

      break;
   }
}

void ArcShape::drawWithInitialPointInThirdQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(currentFinalPoint)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,270 - prevAngle,nextAngle,scale);

      break;
      case DOIS:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

      drawPoints(points,270 - prevAngle,90 + nextAngle,scale);

      break;
      case TRES:
      {
         double angInit = calcAngle(diffCordenates(currentCenterPoint.y,currentInitialPoint.y),raio);
         double angFinal = calcAngle(diffCordenates(currentCenterPoint.y,currentFinalPoint.y),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
            nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

            drawPoints(points,270 - nextAngle,180 + prevAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
            nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

            drawPoints(points,270 - prevAngle,180 + nextAngle,scale);
         }
      }
      break;
      case QUATRO:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,360 - nextAngle,180 + prevAngle,scale);
      break;
   }
}

void ArcShape::drawWithInitialPointInFourthQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(currentFinalPoint)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

      drawPoints(points,90 - nextAngle,0,scale);
      drawPoints(points,360,270 + prevAngle,scale);

      break;
      case DOIS:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

      drawPoints(points,180 - nextAngle,0,scale);
      drawPoints(points,360,270 + prevAngle,scale);

      break;
      case TRES:
      prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
      nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

      drawPoints(points,270 - nextAngle,0,scale);
      drawPoints(points,360,270 + prevAngle,scale);

      break;
      case QUATRO:
      {
         double angInit = calcAngle(diffCordenates(currentCenterPoint.y,currentInitialPoint.y),raio);
         double angFinal = calcAngle(diffCordenates(currentCenterPoint.y,currentFinalPoint.y),distanceInitFinal);

         if (angInit > angFinal) {
            prevAngle = calcAngle(diffCordenates(currentInitialPoint.x,currentCenterPoint.x),raio);
            nextAngle = calcAngle(diffCordenates(currentFinalPoint.y,currentCenterPoint.y),distanceInitFinal);

            drawPoints(points,360 - nextAngle,270 + prevAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(currentInitialPoint.y,currentCenterPoint.y),raio);
            nextAngle = calcAngle(diffCordenates(currentFinalPoint.x,currentCenterPoint.x),distanceInitFinal);

            drawPoints(points,360 - prevAngle,270 + nextAngle,scale);
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

QUADRANT ArcShape::calcQuadrantPoint(const Point& point)
{
   if (point.x > currentCenterPoint.x) {
      return (point.y > currentCenterPoint.y) ? QUATRO : UM ;
   }
   else {
      return (point.y > currentCenterPoint.y) ? TRES : DOIS ;
   }
}

///////////////////////////////////////////////////////////////////////////////

double ArcShape::calcAngle(double catetoOposto,double hipo)
{
   return asin(catetoOposto / hipo) * 180 / PI;
}

double ArcShape::calcPitagoras(const Point point1,const Point point2)
{
   int x = diffCordenates(point1.x,point2.x);
   int y = diffCordenates(point1.y,point2.y);
   return sqrt(pow(x,2) + pow(y,2));
}
