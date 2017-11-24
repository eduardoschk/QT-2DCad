#include "Arc.h"
#include <Math.h>
#include <QtWidgets>
#include <sstream>

#define PI 3.14159265

Arc::Arc(QPoint& _centerPoint,QPoint& _initialPoint,QPoint& _finalPoint) 
{
   center= _centerPoint;
   finalPoint= _finalPoint;
   initialPoint= _initialPoint; 
   raio= calcPitagoras(center,initialPoint);
}

///////////////////////////////////////////////////////////////////////////////

QRectF Arc::boundingRect() const
{
   return QRectF(0,0,1920,1200);
}

void Arc::paint(QPainter* painter,const QStyleOptionGraphicsItem* item,QWidget* widget)
{
   switch (calcQuadrantPoint(initialPoint)) {
      case UM:       drawWithInitialPointInFirstQuadrant(*painter,calcPitagoras(center,finalPoint));     break;
      case DOIS:     drawWithInitialPointInSecondQuadrant(*painter,calcPitagoras(center,finalPoint));    break;
      case TRES:     drawWithInitialPointInThirdQuadrant(*painter,calcPitagoras(center,finalPoint));     break;
      case QUATRO:   drawWithInitialPointInFourthQuadrant(*painter,calcPitagoras(center,finalPoint));    break;
   }
}

///////////////////////////////////////////////////////////////////////////////

void Arc::drawPoints(QPainter& painter,const float initAngule,const float finalAngule)
{
   QPainterPath path;
   path.moveTo(calcPointOnAngle(fmod(initAngule,361.0f)));
   for (float ang= fmod(initAngule,361.0f) ; ang >= fmod(finalAngule,360); ang-= 0.5f) {
      path.lineTo(calcPointOnAngle(ang));
   }
   painter.drawPath(path);
}

///////////////////////////////////////////////////////////////////////////////

QPoint Arc::calcPointOnAngle(float angle)
{
   float y= raio * (sin(angle * PI / 180));
   float x= raio * (cos(angle * PI / 180));

   return QPoint(center.x() + x, center.y() - y);

  /* if (angle >= 0 && angle <= 90)
      return QPoint(center.x() + x,center.y() - y);
   else if (angle >= 90 && angle <= 180)
      return QPoint(center.x() - x,center.y() - y);
   else if (angle >= 180 && angle <= 270)
      return QPoint(center.x() - x,center.y() + y);
   else if (angle >= 270 && angle <= 360)
      return QPoint(center.x() + x,center.y() + y);*/
}

///////////////////////////////////////////////////////////////////////////////

void Arc::drawWithInitialPointInFirstQuadrant(QPainter& painter,float distanceInitFinal)
{
   float prevAngle,nextAngle;

   switch (calcQuadrantPoint(finalPoint)) {
      case UM:
      {
         float angInit = calcAngule(diffCordenates(center.y(),initialPoint.y()),raio);
         float angFinal = calcAngule(diffCordenates(center.y(),finalPoint.y()),distanceInitFinal);
         if (angInit > angFinal) {
            prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

            drawPoints(painter,90 - prevAngle,nextAngle);
         }
         else {
            prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

            drawPoints(painter,90 - nextAngle,prevAngle);
         }
      }
      break;
      case DOIS:
      prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,180 - nextAngle,prevAngle);

      break;
      case TRES:
      prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

      drawPoints(painter,270 - nextAngle,prevAngle);

      break;
      case QUATRO:
      prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,360 - nextAngle,prevAngle);

      break;
   }
}

void Arc::drawWithInitialPointInSecondQuadrant(QPainter& painter,float distanceInitFinal)
{
   float prevAngle,nextAngle;

   switch (calcQuadrantPoint(finalPoint)) {
      case UM:
      prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,180 - prevAngle,nextAngle);

      break;
      case DOIS:
      {
         float angInit = calcAngule(diffCordenates(center.y(),initialPoint.y()),raio);
         float angFinal = calcAngule(diffCordenates(center.y(),finalPoint.y()),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

            drawPoints(painter,180 - prevAngle,90 + nextAngle);
         }
         else {
            prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

            drawPoints(painter,180 - nextAngle,90 + prevAngle);
         }
      }
      break;
      case TRES:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

      drawPoints(painter,270 - nextAngle,90 + prevAngle);

      break;
      case QUATRO:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,360 - nextAngle,90 + prevAngle);

      break;
   }
}

void Arc::drawWithInitialPointInThirdQuadrant(QPainter& painter,float distanceInitFinal)
{
   float prevAngle,nextAngle;

   switch (calcQuadrantPoint(finalPoint)) {
      case UM:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,270 - prevAngle,nextAngle);

      break;
      case DOIS:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

      drawPoints(painter,270 - prevAngle,90 + nextAngle);

      break;
      case TRES:
      {
         float angInit = calcAngule(diffCordenates(center.y(),initialPoint.y()),raio);
         float angFinal = calcAngule(diffCordenates(center.y(),finalPoint.y()),distanceInitFinal);

         if (angInit < angFinal) {
            prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

            drawPoints(painter,270 - nextAngle,180 + prevAngle);
         }
         else {
            prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

            drawPoints(painter,270 - prevAngle,180 + nextAngle);
         }
      }
      break;
      case QUATRO:
      prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,360 - nextAngle,180 + prevAngle);
      break;
   }
}

void Arc::drawWithInitialPointInFourthQuadrant(QPainter& painter,float distanceInitFinal)
{
   float prevAngle,nextAngle;

   switch (calcQuadrantPoint(finalPoint)) {
      case UM:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

      drawPoints(painter,90 - nextAngle,0);
      drawPoints(painter,360,270 + prevAngle);

      break;
      case DOIS:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

      drawPoints(painter,180 - nextAngle,0);
      drawPoints(painter,360,270 + prevAngle);

      break;
      case TRES:
      prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
      nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

      drawPoints(painter,270 - nextAngle,0);
      drawPoints(painter,360,270 + prevAngle);

      break;
      case QUATRO:
      {
         float angInit = calcAngule(diffCordenates(center.y(),initialPoint.y()),raio);
         float angFinal = calcAngule(diffCordenates(center.y(),finalPoint.y()),distanceInitFinal);

         if (angInit > angFinal) {
            prevAngle = calcAngule(diffCordenates(initialPoint.x(),center.x()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.y(),center.y()),distanceInitFinal);

            drawPoints(painter,360 - nextAngle,270 + prevAngle);
         }
         else {
            prevAngle = calcAngule(diffCordenates(initialPoint.y(),center.y()),raio);
            nextAngle = calcAngule(diffCordenates(finalPoint.x(),center.x()),distanceInitFinal);

            drawPoints(painter,360 - prevAngle,270 + nextAngle);
         }
      }
      break;
   }
}

///////////////////////////////////////////////////////////////////////////////

int Arc::diffCordenates(const int coord1,const int coord2)
{
   int greater = fmax(coord1,coord2);
   int less = (greater == coord1) ? coord2 : coord1;
   return greater - less;
}

QUADRANT Arc::calcQuadrantPoint(const QPoint& point)
{
   if (point.x() > center.x()) {
      return (point.y() > center.y()) ? QUATRO : UM ;
   }
   else {
      return (point.y() > center.y()) ? TRES : DOIS ;
   }
}

///////////////////////////////////////////////////////////////////////////////

float Arc::calcAngule(float catetoOposto,float hipo)
{
   return asin(catetoOposto / hipo) * 180 / PI;
}

double Arc::calcPitagoras(const QPoint& point1,const QPoint& point2)
{
   int x = diffCordenates(point1.x(),point2.x());
   int y = diffCordenates(point1.y(),point2.y());
   return sqrt(pow(x,2) + pow(y,2));
}