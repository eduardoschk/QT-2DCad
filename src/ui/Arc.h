#pragma once
#ifndef INCLUDED_ARC_H
#define INCLUDED_ARC_H

#include <QGraphicsItem>

enum QUADRANT { UM , DOIS , TRES , QUATRO };

class Arc :
    public QGraphicsItem
{
private:
    QPoint center;
    QPoint initialPoint;
    QPoint finalPoint;

    float raio;

    void printSupportLines( QPainter & painter );
    void drawPoints( QPainter & painter , const float initAngule , const float finalAngule );

    int diffCordenates( const int value1 , const int value2 );
    QUADRANT calcQuadrantPoint( const QPoint & point );

    void drawWithInitialPointInFirstQuadrant( QPainter & painter , float distanceInitFinal );
    void drawWithInitialPointInSecondQuadrant( QPainter & painter , float distanceInitFinal );
    void drawWithInitialPointInThirdQuadrant( QPainter & painter , float distanceInitFinal );
    void drawWithInitialPointInFourthQuadrant( QPainter & painter , float distanceInitFinal );

    float calcAngule( float catetoOposto , float hipo );
    double calcPitagoras( const QPoint & point1 , const QPoint & point2 );

public:
    ~Arc() {}
    Arc(QPoint & _centerPoint, QPoint & _initialPoint, QPoint & _finalPoint, float scale);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
};

#endif // INCLUDED_ARC_H