#include "Bezier.h"
#include <Math.h>
#include <QtWidgets>
#include <iostream>
#include <QMatrix>

Bezier::Bezier(QPoint & p1, QPoint & p2, QPoint & p3, float scale) 
{
    initial = p1 / scale;
    middle = p2 / scale;
    final = p3 / scale;
}

QRectF Bezier::boundingRect() const
{
    return QRectF(0, 0, 600, 600);
}

QPainterPath Bezier::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 0, 0);
    return path;
}

void Bezier::paint(QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget)
{
    qreal scale = QStyleOptionGraphicsItem::levelOfDetailFromTransform(painter->worldTransform());

    painter->setRenderHint(QPainter::Antialiasing, true);
    for (float t = 0; t <= 1; t += 0.0005) {
        float resultX = pow((1 - t), 2) * initial.x() + 2 * t * (1-t) * middle.x() + pow(t, 2) * final.x();
        float resultY = pow((1 - t), 2) * initial.y() + 2 * t * (1 - t) * middle.y() + pow(t, 2) * final.y();
        painter->drawPoint(QPoint(resultX, resultY));
    }
}