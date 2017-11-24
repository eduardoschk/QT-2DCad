#pragma once
#ifndef INCLUDED_BEZIER_H
#define INCLUDED_BEZIER_H

#include <QGraphicsItem>

class Bezier : public QGraphicsItem
{
private:
   QPoint initial;
   QPoint middle;
   QPoint final;

   QPoint calcPoint(float distance);
   float calcX(float distance);
   float calcY(float distance);

public:
   ~Bezier() {}
    Bezier(QPoint& p1,QPoint& p2,QPoint& p3);

    QRectF boundingRect() const override;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* item,QWidget* widget) override;
};

#endif // INCLUDED_LINE_H