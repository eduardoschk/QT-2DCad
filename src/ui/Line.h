#pragma once
#ifndef INCLUDED_LINE_H
#define INCLUDED_LINE_H

#include <QGraphicsItem>

class Line : public QGraphicsItem
{
private:
   QPoint initial;
   QPoint final;

public:
    Line(QPoint& p1,QPoint& p2);
    ~Line() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter,const QStyleOptionGraphicsItem* item,QWidget* widget) override;
};

#endif // INCLUDED_LINE_H