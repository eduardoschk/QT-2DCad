#pragma once
#ifndef INCLUDED_LINE_H
#define INCLUDED_LINE_H

#include <QGraphicsItem>

class Line 
    : public QGraphicsItem
{
public:
    Line(QPoint & p1, QPoint & p2 , float scale);
    ~Line() {}

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    QPoint initial;
    QPoint final;
};

#endif // INCLUDED_LINE_H