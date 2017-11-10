#pragma once
#ifndef INCLUDED_BEZIER_H
#define INCLUDED_BEZIER_H

#include <QGraphicsItem>

class Bezier 
    : public QGraphicsItem
{
public:
    Bezier(QPoint & p1, QPoint & p2, QPoint & p3, float scale);
    ~Bezier() {}

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    QPoint initial;
    QPoint middle;
    QPoint final;
};

#endif // INCLUDED_LINE_H