#include "Line.h"
#include <QtWidgets>
#include <iostream>

Line::Line(QPoint & p1, QPoint & p2, float scale )
{
    initial= p1 / scale;
    final= p2 / scale;
}

QRectF Line::boundingRect() const
{
    if (initial.y() > final.y()) {
        if (initial.x() > final.x()) 
            return QRect(final, initial);
        else 
            return QRectF(QPoint(initial.x(), final.y()), QPoint(final.x(), initial.y()));
    }
    else {
        if (initial.x() > final.x()) 
            return QRectF(QPoint(final.x(), initial.y()), QPoint(initial.x(), final.y()));
        else 
            return QRect(initial, final);
    }
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::red, 2));

    int x= initial.x();
    int y= initial.y();

    int dy = final.y() - initial.y();
    int dx = final.x() - initial.x();
    int stepX , stepY;

    dy < 0 ? stepY= -1 : stepY= 1;
    dy *= stepY;

    dx < 0 ? stepX= -1 : stepX= 1;
    dx *= stepX;

    if ( dx > dy )
    {
        for ( int fraction = dy - dx ; x != final.x() ; painter->drawPoint( x , y ) )
        {
            if ( fraction >= 0 )
            {
                y += stepY;
                fraction -= dx;
            }
            x += stepX;
            fraction += dy;
        }
    }
    else {
        for ( int fraction = dx - dy ; y != final.y() ; painter->drawPoint( x , y )) {
            if ( fraction >= 0 ) {
                x += stepX;
                fraction -= dy;
            }
            y += stepY;
            fraction += dx;
        }
    }

}