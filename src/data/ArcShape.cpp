#include "ArcShape.h"
#include "Point.h"

#define PI 3.14159265

ArcShape::~ArcShape()
{
}

ArcShape::ArcShape(int _id,Point _center,Point _initial,Point _final) : Shape(_id)
{
   final= _final;
   center= _center;
   initial= _initial;
   raio= calcPitagoras(center,initial);
}

///////////////////////////////////////////////////////////////////////////////

int ArcShape::getType()
{
   return SHAPE_TYPE::ARC;
}

std::deque<Point> ArcShape::getPointsToDraw(float scale)
{
   std::deque<Point> points;
   switch (calcQuadrantPoint(initial)) {
      case UM:       drawWithInitialPointInFirstQuadrant(points,calcPitagoras(center,final),scale);     break;
      case DOIS:     drawWithInitialPointInSecondQuadrant(points,calcPitagoras(center,final),scale);    break;
      case TRES:     drawWithInitialPointInThirdQuadrant(points,calcPitagoras(center,final),scale);     break;
      case QUATRO:   drawWithInitialPointInFourthQuadrant(points,calcPitagoras(center,final),scale);    break;
   }
   return points;
}

std::deque<Point> ArcShape::getPointsToDrawInRect(float scale,Rect rect)
{
   std::deque<Point> pointInRect;
   std::deque<Point> allPoints= getPointsToDraw(scale);

   for (Point point : allPoints) {
      if (point.on(rect))
         pointInRect.push_back(point - Point(rect.initialX,rect.initialY));
   }
   return pointInRect;
}

std::deque<Point> ArcShape::getSelectedPoints()
{
   std::deque<Point> points;
   points.push_back(center);
   points.push_back(initial);
   points.push_back(final);
   return points;
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::drawPoints(std::deque<Point>& points,const double initAngule,const double finalAngule,float scale)
{
   for (double ang= fmod(initAngule,361.0f) ; ang >= fmod(finalAngule,360); ang-= 0.5f)
     points.push_back(calcPointOnAngle(ang) * scale);
}

///////////////////////////////////////////////////////////////////////////////

Point ArcShape::calcPointOnAngle(double angle)
{
   double y= raio * (sin(angle * PI / 180));
   double x= raio * (cos(angle * PI / 180));

   return Point(center.x + x,center.y - y);
}

///////////////////////////////////////////////////////////////////////////////

void ArcShape::drawWithInitialPointInFirstQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(final)) {
      case UM:
      {
         double angInit= calcAngle(diffCordenates(center.y,initial.y),raio);
         double angFinal= calcAngle(diffCordenates(center.y,final.y),distanceInitFinal);
         if (angInit > angFinal) {
            prevAngle= calcAngle(diffCordenates(initial.x,center.x),raio);
            nextAngle= calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

            drawPoints(points,90 - prevAngle,nextAngle,scale);
         }
         else {
            prevAngle= calcAngle(diffCordenates(initial.y,center.y),raio);
            nextAngle= calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

            drawPoints(points,90 - nextAngle,prevAngle,scale);
         }
      }
      break;
      case DOIS:
      prevAngle= calcAngle(diffCordenates(initial.y,center.y),raio);
      nextAngle= calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,180 - nextAngle,prevAngle,scale);

      break;
      case TRES:
      prevAngle= calcAngle(diffCordenates(initial.y,center.y),raio);
      nextAngle= calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

      drawPoints(points,270 - nextAngle,prevAngle,scale);

      break;
      case QUATRO:
      prevAngle= calcAngle(diffCordenates(initial.y,center.y),raio);
      nextAngle= calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,360 - nextAngle,prevAngle,scale);

      break;
   }
}

void ArcShape::drawWithInitialPointInSecondQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(final)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(initial.y,center.y),raio);
      nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,180 - prevAngle,nextAngle,scale);

      break;
      case DOIS:
      {
         double angInit = calcAngle(diffCordenates(center.y,initial.y),raio);
         double angFinal = calcAngle(diffCordenates(center.y,final.y),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngle(diffCordenates(initial.y,center.y),raio);
            nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

            drawPoints(points,180 - prevAngle,90 + nextAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
            nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

            drawPoints(points,180 - nextAngle,90 + prevAngle,scale);
         }
      }
      break;
      case TRES:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

      drawPoints(points,270 - nextAngle,90 + prevAngle,scale);

      break;
      case QUATRO:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,360 - nextAngle,90 + prevAngle,scale);

      break;
   }
}

void ArcShape::drawWithInitialPointInThirdQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(final)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,270 - prevAngle,nextAngle,scale);

      break;
      case DOIS:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

      drawPoints(points,270 - prevAngle,90 + nextAngle,scale);

      break;
      case TRES:
      {
         double angInit = calcAngle(diffCordenates(center.y,initial.y),raio);
         double angFinal = calcAngle(diffCordenates(center.y,final.y),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngle(diffCordenates(initial.y,center.y),raio);
            nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

            drawPoints(points,270 - nextAngle,180 + prevAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
            nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

            drawPoints(points,270 - prevAngle,180 + nextAngle,scale);
         }
      }
      break;
      case QUATRO:
      prevAngle = calcAngle(diffCordenates(initial.y,center.y),raio);
      nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,360 - nextAngle,180 + prevAngle,scale);
      break;
   }
}

void ArcShape::drawWithInitialPointInFourthQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale)
{
   double prevAngle,nextAngle;

   switch (calcQuadrantPoint(final)) {
      case UM:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

      drawPoints(points,90 - nextAngle,0,scale);
      drawPoints(points,360,270 + prevAngle,scale);

      break;
      case DOIS:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

      drawPoints(points,180 - nextAngle,0,scale);
      drawPoints(points,360,270 + prevAngle,scale);

      break;
      case TRES:
      prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
      nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

      drawPoints(points,270 - nextAngle,0,scale);
      drawPoints(points,360,270 + prevAngle,scale);

      break;
      case QUATRO:
      {
         double angInit = calcAngle(diffCordenates(center.y,initial.y),raio);
         double angFinal = calcAngle(diffCordenates(center.y,final.y),distanceInitFinal);

         if (angInit > angFinal) {
            prevAngle = calcAngle(diffCordenates(initial.x,center.x),raio);
            nextAngle = calcAngle(diffCordenates(final.y,center.y),distanceInitFinal);

            drawPoints(points,360 - nextAngle,270 + prevAngle,scale);
         }
         else {
            prevAngle = calcAngle(diffCordenates(initial.y,center.y),raio);
            nextAngle = calcAngle(diffCordenates(final.x,center.x),distanceInitFinal);

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
   if (point.x > center.x) {
      return (point.y > center.y) ? QUATRO : UM ;
   }
   else {
      return (point.y > center.y) ? TRES : DOIS ;
   }
}

///////////////////////////////////////////////////////////////////////////////

double ArcShape::calcAngle(double catetoOposto,double hipo)
{
   return asin(catetoOposto / hipo) * 180 / PI;
}

double ArcShape::calcPitagoras(const Point& point1,const Point& point2)
{
   int x = diffCordenates(point1.x,point2.x);
   int y = diffCordenates(point1.y,point2.y);
   return sqrt(pow(x,2) + pow(y,2));
}
