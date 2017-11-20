#include "DrawArea.h"

#include <QtMath>
#include <QScrollBar>
#include <QMouseEvent>

#include "Line.h"
#include "Bezier.h"
#include "Arc.h"

int sizeScroll= 10;

DrawArea::~DrawArea()
{
   for ( int i= 0 ; i < itens.size() ; ++i )
      delete itens[i];
   itens.clear();
   delete scene;
   if ( hScrollBar )
      delete hScrollBar;
   if ( vScrollBar )
      delete vScrollBar;
   if ( currentItem )
      delete currentItem;
}

DrawArea::DrawArea( int _widthArea , int _heightArea , int _limitWidth , int _limitHeight ) :
   widthDraw( _widthArea ) , heightDraw( _heightArea ) ,
   scene( new QGraphicsScene( this ) ) ,
   limitWidth( _limitWidth ) , limitHeight( _limitHeight )
{
   configureDefaultValues();
   configureScrollBar();

   scene->setSceneRect( QRect( QPoint( 0 , 0 ) , QPoint( widthDraw , heightDraw ) ) );
   changedSize();
}

void DrawArea::configureDefaultValues()
{
   scale= 1;

   setScene( scene );

   currentShape= LINE;
   currentItem= nullptr;

   setAutoFillBackground( true );
   setBackgroundRole( QPalette::Base );

   widthHorizontalScrollBar= heigthVerticalScrollBar= 0;
}

void DrawArea::configureScrollBar()
{
   hScrollBar = horizontalScrollBar();
   vScrollBar = verticalScrollBar();

   connect( hScrollBar , SIGNAL( valueChanged( int ) ) , this , SLOT( widthScrollChanged( int ) ) );
   connect( vScrollBar , SIGNAL( valueChanged( int ) ) , this , SLOT( heightScrollChanged( int ) ) );
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::setScale( float _scale )
{
    scale = _scale;
    QMatrix ma;
    ma.scale( qreal( scale ) , qreal( scale ) );
    setMatrix( ma );        
    changedSize();
}

QPoint DrawArea::correctPointInRelationToScrollbar( QPoint point )
{
    return point+= QPoint(widthHorizontalScrollBar, heigthVerticalScrollBar);
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::changedSize()
{
   int widthReal= calcNewDrawingWidth();
   int heigthReal= calcNewDrawingHeight();

    setFixedSize( widthReal , heigthReal );
}

int DrawArea::calcNewDrawingWidth()
{
   return ( sizeScroll + widthDraw * scale > limitWidth) ? limitWidth : ( sizeScroll + widthDraw * scale );
}

int DrawArea::calcNewDrawingHeight()
{
   return ( sizeScroll + heightDraw * scale > limitHeight ) ? ( limitHeight - sizeScroll ) : ( sizeScroll + heightDraw * scale ) ;
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::heightScrollChanged( int value )
{
   heigthVerticalScrollBar = value;
}

void DrawArea::widthScrollChanged( int value )
{
   widthHorizontalScrollBar = value;
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::mousePressEvent( QMouseEvent * event )
{
   if ( currentShape == SHAPE_TYPE::LINE ) {
      points[0] = event->pos();
   }
   else {
      if ( points[0].isNull() )
         points[0] = event->pos();
      else
         points[1] = event->pos();
   }
   setMouseTracking( true );
   event->accept();
}

void DrawArea::mouseMoveEvent(QMouseEvent * event)
{
    QPoint p = event->pos();
    if (currentItem)
        delete currentItem;

    switch ( currentShape ) 
    {
    case LINE:      currentItem = new Line( correctPointInRelationToScrollbar( points[0] ) , correctPointInRelationToScrollbar( event->pos() ) , scale );                                           break;
    case BEZIER:    currentItem = new Bezier( correctPointInRelationToScrollbar( points[0] ) , correctPointInRelationToScrollbar( points[1] ) , correctPointInRelationToScrollbar( event->pos() ) , scale );       break;
    case ARC:       currentItem = new Arc( correctPointInRelationToScrollbar( points[0] ) , correctPointInRelationToScrollbar( points[1] ) , correctPointInRelationToScrollbar( event->pos() ) , scale );          break;
    }

    scene->addItem(currentItem);
    scene->update();
    event->accept();
}

void DrawArea::mouseReleaseEvent(QMouseEvent * event)
{
    if ( currentShape == SHAPE_TYPE::LINE ) {
        itens.push_back( currentItem );
        QPoint p = event->pos();
        emit( drawLineFinish( points[0] , event->pos() ) );
        clearPoints();
    }
    else {
        if ( !points[1].isNull() ) {
            itens.push_back( currentItem );
            if (currentShape == SHAPE_TYPE::ARC )
                emit( drawArcFinish( points[0] , points[1] , event->pos() ) );
            else
                emit( drawBezierFinish( points[0] , points[1] , event->pos() ) );
            clearPoints();
        }
    }
    setMouseTracking( false );
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::clearPoints()
{
    currentItem = nullptr;
    points[0]=  points[1]= QPoint();
}

void DrawArea::setShapeToDraw( SHAPE_TYPE shape )
{
    clearPoints();
    currentShape= shape;
}

void DrawArea::setLimitArea( const QSize & size )
{
    limitWidth= size.width();
    limitHeight= size.height();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::drawLine( QPoint initial , QPoint final )
{
    scene->addItem( new Line( correctPointInRelationToScrollbar( initial ) , correctPointInRelationToScrollbar( final ) , scale ));
    scene->update();
}

void DrawArea::drawBezier( QPoint initial , QPoint control , QPoint final )
{
    scene->addItem( new Bezier( correctPointInRelationToScrollbar( initial ) , correctPointInRelationToScrollbar( control ) , correctPointInRelationToScrollbar( final ) , scale ) );
    scene->update();
}

void DrawArea::drawArc( QPoint center , QPoint initial , QPoint final )
{
    scene->addItem( new Arc( correctPointInRelationToScrollbar( center ) , correctPointInRelationToScrollbar( initial ) , correctPointInRelationToScrollbar( final ) , scale ) );
    scene->update();
}