#include "Arc.h"
#include <Math.h>
#include <QtWidgets>
#include <sstream>

#define PI 3.14159265

Arc::Arc( QPoint & _centerPoint , QPoint & _initialPoint , QPoint & _finalPoint , float scale ) :
   center( _centerPoint / scale) , initialPoint( _initialPoint / scale ) , finalPoint( _finalPoint / scale ), raio(calcPitagoras( center , initialPoint )) {}

///////////////////////////////////////////////////////////////////////////////

QRectF Arc::boundingRect() const
{
    return QRectF(0, 0, 600, 600);
}

void Arc::paint(QPainter * painter, const QStyleOptionGraphicsItem * item, QWidget * widget)
{
   switch ( calcQuadrantPoint( initialPoint ) ) {
   case UM:       drawWithInitialPointInFirstQuadrant( *painter , calcPitagoras( center , finalPoint ) );     break;
   case DOIS:     drawWithInitialPointInSecondQuadrant( *painter , calcPitagoras( center , finalPoint ) );    break;
   case TRES:     drawWithInitialPointInThirdQuadrant( *painter , calcPitagoras( center , finalPoint ) );     break;
   case QUATRO:   drawWithInitialPointInFourthQuadrant( *painter , calcPitagoras( center , finalPoint ) );    break;
   }
}

///////////////////////////////////////////////////////////////////////////////

void Arc::drawPoints( QPainter & painter, const float initAngule , const float finalAngule )
{
   for ( float ang = fmod(initAngule, 361.0f) ; ang >= fmod( finalAngule , 360 ); ang -= 0.5f ) {
      float y = abs( raio * ( sin ( ang * PI / 180 ) ) );
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

///////////////////////////////////////////////////////////////////////////////

void Arc::drawWithInitialPointInFirstQuadrant( QPainter & painter , float distanceInitFinal )
{
   float prevAngle , nextAngle;
   
   switch ( calcQuadrantPoint( finalPoint ) ) {
   case UM: {
      float angInit = calcAngule( diffCordenates( center.y() , initialPoint.y() ) , raio );
      float angFinal = calcAngule( diffCordenates( center.y() , finalPoint.y() ) , distanceInitFinal );
      if ( angInit > angFinal ) {
         prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

         drawPoints( painter , 90 - prevAngle , nextAngle );
      }
      else {
         prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

         drawPoints( painter , 90 - nextAngle , prevAngle );
      }
   }
   break;
   case DOIS:
      prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 180 - nextAngle , prevAngle );

   break;
   case TRES:
      prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

      drawPoints( painter , 270 - nextAngle , prevAngle );

   break;
   case QUATRO:
      prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 360 - nextAngle , prevAngle );

   break;
   }
}

void Arc::drawWithInitialPointInSecondQuadrant( QPainter & painter , float distanceInitFinal )
{
   float prevAngle , nextAngle;

   switch ( calcQuadrantPoint( finalPoint ) ) {
   case UM:
      prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 180 - prevAngle , nextAngle );

   break;
   case DOIS: {
      float angInit = calcAngule( diffCordenates( center.y() , initialPoint.y() ) , raio );
      float angFinal = calcAngule( diffCordenates( center.y() , finalPoint.y() ) , distanceInitFinal );

      if ( angInit < angFinal ) {
         prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

         drawPoints( painter , 180 - prevAngle , 90 + nextAngle );
      }
      else {
         prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

         drawPoints( painter , 180 - nextAngle , 90 + prevAngle );
      }
   }
   break;
   case TRES:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

      drawPoints( painter , 270 - nextAngle , 90 + prevAngle );

   break;
   case QUATRO:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 360 - nextAngle , 90 + prevAngle );

   break;
   }
}

void Arc::drawWithInitialPointInThirdQuadrant( QPainter & painter , float distanceInitFinal )
{
   float prevAngle , nextAngle;

   switch ( calcQuadrantPoint( finalPoint ) ) {
   case UM:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 270 - prevAngle , nextAngle );

   break;
   case DOIS:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

      drawPoints( painter , 270 - prevAngle , 90 + nextAngle );

   break;
   case TRES: {
      float angInit = calcAngule( diffCordenates( center.y() , initialPoint.y() ) , raio );
      float angFinal = calcAngule( diffCordenates( center.y() , finalPoint.y() ) , distanceInitFinal );

      if ( angInit < angFinal ) {
         prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

         drawPoints( painter , 270 - nextAngle , 180 + prevAngle );
      }
      else {
         prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

         drawPoints( painter , 270 - prevAngle , 180 + nextAngle );
      }
   }
   break;
   case QUATRO:
      prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 360 - nextAngle , 180 + prevAngle );
      break;
   }
}

void Arc::drawWithInitialPointInFourthQuadrant( QPainter & painter , float distanceInitFinal )
{
   float prevAngle , nextAngle;

   switch ( calcQuadrantPoint( finalPoint ) ) {
   case UM:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

      drawPoints( painter , 90 - nextAngle , 0 );
      drawPoints( painter , 360 , 270 + prevAngle );

   break;
   case DOIS:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

      drawPoints( painter , 180 - nextAngle , 0 );
      drawPoints( painter , 360 , 270 + prevAngle );

   break;
   case TRES:
      prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
      nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

      drawPoints( painter , 270 - nextAngle , 0 );
      drawPoints( painter , 360 , 270 + prevAngle );

   break;
   case QUATRO: {
      float angInit = calcAngule( diffCordenates( center.y() , initialPoint.y() ) , raio );
      float angFinal = calcAngule( diffCordenates( center.y() , finalPoint.y() ) , distanceInitFinal );

      if ( angInit > angFinal ) {
         prevAngle = calcAngule( diffCordenates( initialPoint.x() , center.x() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.y() , center.y() ) , distanceInitFinal );

         drawPoints( painter , 360 - nextAngle , 270 + prevAngle );
      }
      else {
         prevAngle = calcAngule( diffCordenates( initialPoint.y() , center.y() ) , raio );
         nextAngle = calcAngule( diffCordenates( finalPoint.x() , center.x() ) , distanceInitFinal );

         drawPoints( painter , 360 - prevAngle , 270 + nextAngle );
      }
   }
   break;
   }
}

///////////////////////////////////////////////////////////////////////////////

int Arc::diffCordenates( const int value1 , const int value2 )
{
   int greater = fmax( value1 , value2 );
   int less = ( greater == value1 ) ? value2 : value1;
   return greater - less;
}

QUADRANT Arc::calcQuadrantPoint( const QPoint & point )
{
   if ( point.x() > center.x() ) {
      return ( point.y() > center.y() ) ? QUATRO : UM ;
   }
   else {
      return ( point.y() > center.y() ) ? TRES : DOIS ;
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