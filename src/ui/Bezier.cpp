#include "Bezier.h"
#include <Math.h>
#include <QtWidgets>

Bezier::Bezier(QPoint & p1, QPoint & p2, QPoint & p3, float scale) :
   initial( p1 / scale ) , middle( p2 / scale ), final( p3 / scale ) {}

QRectF Bezier::boundingRect() const
{
    return QRectF(0, 0, 600, 600);
}

void Bezier::paint(QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget)
{
    for (float distance = 0; distance <= 1; distance += 0.0005f) 
        painter->drawPoint( QPoint( calcX( distance ), calcY( distance )));
}

float Bezier::calcX( float distance )
{
   return pow( ( 1 - distance ) , 2 ) * initial.x() + 2 * distance * ( 1 - distance ) * middle.x() + pow( distance , 2 ) * final.x();
}

float Bezier::calcY( float distance )
{
   return pow( ( 1 - distance ) , 2 ) * initial.y() + 2 * distance * ( 1 - distance ) * middle.y() + pow( distance , 2 ) * final.y();
}