#include "Line.h"
#include <QtWidgets>

Line::Line(QPoint& p1,QPoint& p2)
{
   initial= p1;
   final= p2;
}

///////////////////////////////////////////////////////////////////////////////

QRectF Line::boundingRect() const
{
   if (initial.y() > final.y()) {
      if (initial.x() > final.x())
         return QRect(final,initial);
      else
         return QRectF(QPoint(initial.x(),final.y()),QPoint(final.x(),initial.y()));
   }
   else {
      if (initial.x() > final.x())
         return QRectF(QPoint(final.x(),initial.y()),QPoint(initial.x(),final.y()));
      else
         return QRect(initial,final);
   }
}

void Line::paint(QPainter* painter,const QStyleOptionGraphicsItem* option,QWidget* widget)
{
   int x= initial.x();
   int y= initial.y();

   int distanceY = final.y() - initial.y();
   int distanceX = final.x() - initial.x();
   int stepX,stepY;

   distanceY < 0 ? stepY= -1 : stepY= 1;
   distanceY *= stepY;

   distanceX < 0 ? stepX= -1 : stepX= 1;
   distanceX *= stepX;

   if (distanceX > distanceY) {
      for (int fraction = distanceY - distanceX ; x != final.x() ; painter->drawPoint(x,y)) {
         if (fraction >= 0) {
            y += stepY;
            fraction -= distanceX;
         }
         x += stepX;
         fraction += distanceY;
      }
   }
   else {
      for (int fraction = distanceX - distanceY ; y != final.y() ; painter->drawPoint(x,y)) {
         if (fraction >= 0) {
            x += stepX;
            fraction -= distanceY;
         }
         y += stepY;
         fraction += distanceX;
      }
   }
}