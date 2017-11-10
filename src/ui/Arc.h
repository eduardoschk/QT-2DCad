#pragma once
#ifndef INCLUDED_ARC_H
#define INCLUDED_ARC_H

#include <QGraphicsItem>

class Arc :
    public QGraphicsItem
{
public:
    Arc(QPoint & _centerPoint, QPoint & _initialPoint, QPoint & _finalPoint, float scale);
    ~Arc() {}

    enum QUADRANT {UM, DOIS, TRES, QUATRO};

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    QPoint center;
    QPoint initialPoint;
    QPoint finalPoint;

    float raio;

    QUADRANT quadInitPoint;
    QUADRANT quadFinalPoint;

    void printSupportLines(QPainter & painter);
    void drawPoints( QPainter & painter, const float initAngule , const float finalAngule );

    int diffCordenates(const int value1, const int value2);
    QUADRANT calcQuadrantPoint(const QPoint & point);

    float calcAngule(float catetoOposto, float hipo);
    double calcPitagoras(const QPoint & point1, const QPoint & point2);
};

#endif // INCLUDED_ARC_H