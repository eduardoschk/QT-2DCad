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
    //qreal scale = QStyleOptionGraphicsItem::levelOfDetailFromTransform( painter->worldTransform() );

    //QTransform transform;
    //transform.scale( scale , scale );

    //painter->setTransform( transform );
    
    int dx = initial.x() - final.x();
    int dy = initial.y() - final.y();

    for ( int x = initial.x() ; x < final.x() ; ++x ) {
        int y = initial.y() + dy * ( x - initial.x() ) / dx;
        painter->drawPoint(x, y);
    }
}