#include "Arc.h"
#include <Math.h>
#include <QtWidgets>
#include <sstream>
#include <iostream>

#define PI 3.14159265

Arc::Arc(QPoint & _centerPoint, QPoint & _initialPoint, QPoint & _finalPoint, float scale) 
{
    center= _centerPoint / scale;
    initialPoint= _initialPoint / scale;
    finalPoint= _finalPoint / scale;
}

///////////////////////////////////////////////////////////////////////////////

QRectF Arc::boundingRect() const
{
    return QRectF(0, 0, 600, 600);
}

QPainterPath Arc::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 0, 0);
    return path;
}

void Arc::paint(QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget)
{
    printSupportLines(*painter);

    raio = calcPitagoras(center, initialPoint);
    float distInitFinal = calcPitagoras(center, finalPoint);

    quadInitPoint = calcQuadrantPoint(initialPoint);
    quadFinalPoint = calcQuadrantPoint(finalPoint);

    float anguleAnt;
    float anguleNext;

    painter->setPen(QPen(Qt::red, 2));

    switch (quadInitPoint) {
    case UM:
        switch (quadFinalPoint) {
        case UM: {
            float angInit = calcAngule(diffCordenates(center.y(), initialPoint.y()), raio);
            float angFinal = calcAngule(diffCordenates(center.y(), finalPoint.y()), distInitFinal);
            if (angInit > angFinal) {
                anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
                anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

                drawPoints(*painter,  90 - anguleAnt, anguleNext);
            }
            else {
                anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
                anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

                drawPoints( *painter , 90 - anguleNext , anguleAnt );
            }
            break;
        }
        case DOIS:
            anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

            drawPoints(*painter, 180 - anguleNext, anguleAnt);

            break;
        case TRES:
            anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

            drawPoints( *painter , 270 - anguleNext , anguleAnt );

            break;
        case QUATRO:
            anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

            drawPoints( *painter , 360 - anguleNext , anguleAnt );

            break;
        }
        break;
    case DOIS:
        switch (quadFinalPoint) {
         case UM:
            anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

            drawPoints( *painter , 180 - anguleAnt , anguleNext );

            break;
        case DOIS: {
             float angInit = calcAngule(diffCordenates(center.y(), initialPoint.y()), raio);
             float angFinal = calcAngule(diffCordenates(center.y(), finalPoint.y()), distInitFinal);

             if (angInit < angFinal) {
                 anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
                 anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

                 drawPoints( *painter , 180 - anguleAnt , 90 + anguleNext );
             }
             else {
                 anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
                 anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

                 drawPoints( *painter , 180 - anguleNext , 90 + anguleAnt );
             }
             break;
         }
         case TRES:
             anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
             anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

             drawPoints( *painter , 270 - anguleNext , 90 + anguleAnt );

             break;
         case QUATRO:
             anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
             anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

             drawPoints( *painter , 360 - anguleNext , 90 + anguleAnt );

             break;
        }
        break;
    case TRES:
        switch (quadFinalPoint) {
        case UM:
            anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

            drawPoints( *painter , 270 - anguleAnt , anguleNext );

            break;
        case DOIS:
            anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

            drawPoints( *painter , 270 - anguleAnt , 90 + anguleNext );

            break;
        case TRES: {
            float angInit = calcAngule(diffCordenates(center.y(), initialPoint.y()), raio);
            float angFinal = calcAngule(diffCordenates(center.y(), finalPoint.y()), distInitFinal);

            if (angInit < angFinal) {
                anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
                anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

                drawPoints( *painter , 270 - anguleNext , 180 + anguleAnt );
            }
            else {
                anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
                anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

                drawPoints( *painter , 270 - anguleAnt , 180 + anguleNext );
            }
            break;
        }
        case QUATRO:
            anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

            drawPoints( *painter , 360 - anguleNext , 180 + anguleAnt );
            break;
        }
        break;
    case QUATRO:
        switch (quadFinalPoint) {
        case UM:
            anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

            drawPoints( *painter , 90 - anguleNext , 0 );
            drawPoints( *painter, 360, 270 + anguleAnt );

            break;
        case DOIS:
            anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

            drawPoints( *painter , 180 - anguleNext , 0 );
            drawPoints( *painter , 360 , 270 + anguleAnt );

            break;
        case TRES:
            anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
            anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

            drawPoints( *painter , 270 - anguleNext , 0 );
            drawPoints( *painter , 360 , 270 + anguleAnt );

            break;
        case QUATRO: {

            float angInit = calcAngule(diffCordenates(center.y(), initialPoint.y()), raio);
            float angFinal = calcAngule(diffCordenates(center.y(), finalPoint.y()), distInitFinal);

            if (angInit > angFinal) {
                anguleAnt = calcAngule(diffCordenates(initialPoint.x(), center.x()), raio);
                anguleNext = calcAngule(diffCordenates(finalPoint.y(), center.y()), distInitFinal);

                drawPoints( *painter , 360 - anguleNext , 270 + anguleAnt);
            }
            else {
                anguleAnt = calcAngule(diffCordenates(initialPoint.y(), center.y()), raio);
                anguleNext = calcAngule(diffCordenates(finalPoint.x(), center.x()), distInitFinal);

                drawPoints( *painter , 360 - anguleAnt , 270 + anguleNext );
            }

            break;
        }
        }
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Arc::drawPoints( QPainter & painter, const float initAngule , const float finalAngule )
{
    for ( float ang = fmod(initAngule, 360.00001f) ; ang >= fmod( finalAngule , 360 ); ang -= 0.05f ) {
        float y = abs( raio * ( sin( ang * PI / 180 ) ) );
        float x = abs( sqrt( pow( raio , 2 ) - pow( y , 2 ) ) );

        if ( ang >= 0 && ang <= 90 ) 
            painter.drawPoint( QPoint( center.x() + x , center.y() - y ) );
        else if ( ang >= 90 && ang <= 180 )
            painter.drawPoint( QPoint( center.x() - x , center.y() - y ) );
        else if ( ang >= 180 && ang <= 270 ) 
            painter.drawPoint( QPoint( center.x() - x , center.y() + y ) );
        else if ( ang >= 270 && ang <= 360 ) 
            painter.drawPoint( QPoint( center.x() + x , center.y() + y ) );
    }
}

void Arc::printSupportLines(QPainter & painter)
{
    std::stringstream ss;
    ss << "Inicio [" << initialPoint.x() << "|" << initialPoint.y() << "]";
    std::string initialString = ss.str();

    ss.str( "" );
    ss << "Final [" << finalPoint.x() << "|" << finalPoint.y() << "]";
    std::string finalString = ss.str();

    ss.str( "" );
    ss << "Centro [" << center.x() << "|" << center.y() << "]";
    std::string centerString = ss.str();

    painter.setPen(QPen(Qt::gray, 1));
    painter.drawLine(center, initialPoint);
    painter.drawLine(center, finalPoint);
    painter.drawLine(finalPoint, initialPoint);
    painter.setPen(QPen(Qt::black, 3));
    painter.drawPoint(initialPoint);
    painter.drawText(initialPoint, QString( initialString.c_str()));
    painter.drawPoint(finalPoint);
    painter.drawText(finalPoint, QString( finalString.c_str() ) );
    painter.drawPoint(center);
    painter.drawText(center, QString( centerString.c_str() ) );
}

///////////////////////////////////////////////////////////////////////////////

int Arc::diffCordenates(const int value1, const int value2)
{
    int greater = fmax(value1, value2);
    int less = (greater == value1) ? value2 : value1;
    return greater - less;
}

Arc::QUADRANT Arc::calcQuadrantPoint(const QPoint & point)
{
    if (point.x() > center.x()) {
        if (point.y() > center.y()) {
            return QUATRO;
        }
        else {
            return UM;
        }
    }
    else {
        if (point.y() > center.y()) {
            return TRES;
        }
        else {
            return DOIS;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

float Arc::calcAngule(float catetoOposto, float hipo)
{
    return asin(catetoOposto / hipo) * 180 / PI;
}

double Arc::calcPitagoras(const QPoint & point1, const QPoint & point2)
{
    int x = diffCordenates(point1.x(), point2.x());
    int y = diffCordenates(point1.y(), point2.y());
    return sqrt(pow(x, 2) + pow(y, 2));
}