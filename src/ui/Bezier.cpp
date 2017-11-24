#include "Bezier.h"
#include <Math.h>
#include <QtWidgets>

Bezier::Bezier(QPoint& _initial,QPoint& _middle,QPoint& _final) 
{
   initial= _initial;
   middle= _middle;
   final= _final;
}

///////////////////////////////////////////////////////////////////////////////

QRectF Bezier::boundingRect() const
{
   return QRectF(0,0,1920,1200);
}

void Bezier::paint(QPainter* painter,const QStyleOptionGraphicsItem* item,QWidget* widget)
{
   QPainterPath path;
   path.moveTo(initial);
   for (float distance = 0; distance <= 1; distance += 0.0005f)
      path.lineTo(calcPoint(distance));
   painter->drawPath(path);
}

///////////////////////////////////////////////////////////////////////////////

QPoint Bezier::calcPoint(float distance)
{
   return QPoint(calcX(distance),calcY(distance));
}

float Bezier::calcX(float distance)
{
   return pow((1 - distance),2) * initial.x() + 2 * distance * (1 - distance) * middle.x() + pow(distance,2) * final.x();
}

float Bezier::calcY(float distance)
{
   return pow((1 - distance),2) * initial.y() + 2 * distance * (1 - distance) * middle.y() + pow(distance,2) * final.y();
}