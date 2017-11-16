#include "DrawArea.h"
#include "Line.h"
#include "Bezier.h"
#include "Arc.h"

#include <iostream>
#include <QMouseEvent>
#include <QtMath>
#include <QScrollBar>

DrawArea::DrawArea( int _widthArea , int _heightArea , int _limitWidth , int _limitHeight ) :
    widthDraw( _widthArea ) , heightDraw( _heightArea ) , 
    widthHorizontalScrollBar( 0 ) , heigthVerticalScrollBar( 0 ) , 
    scale( 1 ) , scene( new QGraphicsScene( this ) ) , 
    currentItem( nullptr ) , currentShape( LINE ) ,
    limitWidth ( _limitWidth ), limitHeight( _limitHeight )
{
    setScene( scene );

    setBackgroundRole( QPalette::Base );
    setAutoFillBackground( true );

    scene->setSceneRect( QRect(QPoint (0,0), QPoint(widthDraw , heightDraw )));
    changedSize( );

    hScrollBar = horizontalScrollBar();
    vScrollBar = verticalScrollBar();

    connect( hScrollBar , SIGNAL( valueChanged( int ) ) , this , SLOT( scrollRelease( int ) ) );
    connect( vScrollBar , SIGNAL( valueChanged( int ) ) , this , SLOT( scrollPress( int ) ) );
}

void DrawArea::setScale( float _scale )
{
    scale = _scale;
    QMatrix ma;
    ma.scale( qreal( scale ) , qreal( scale ) );
    setMatrix( ma );        
    changedSize();
}

void DrawArea::mousePressEvent(QMouseEvent * event)
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

QPoint DrawArea::corrigeScrollPoint( QPoint point )
{
    return point+=QPoint(widthHorizontalScrollBar, heigthVerticalScrollBar);
}

void DrawArea::changedSize()
{
    int widthReal , heigthReal;
    if ( 10 + widthDraw * scale > limitWidth )
        widthReal= limitWidth;
    else
        widthReal = 10 + widthDraw * scale;
    if ( 10 + heightDraw * scale > limitHeight )
        heigthReal = limitHeight - 10;
    else
        heigthReal = 10 + heightDraw * scale;

    setFixedSize( widthReal , heigthReal );
}

void DrawArea::mouseMoveEvent(QMouseEvent * event)
{
    QPoint p = event->pos();
    if (currentItem)
        delete currentItem;

    switch ( currentShape ) 
    {
    case LINE:      currentItem = new Line( corrigeScrollPoint( points[0] ) , corrigeScrollPoint( event->pos() ) , scale );                                           break;
    case BEZIER:    currentItem = new Bezier( corrigeScrollPoint( points[0] ) , corrigeScrollPoint( points[1] ) , corrigeScrollPoint( event->pos() ) , scale );       break;
    case ARC:       currentItem = new Arc( corrigeScrollPoint( points[0] ) , corrigeScrollPoint( points[1] ) , corrigeScrollPoint( event->pos() ) , scale );          break;
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

void DrawArea::scrollPress( int i)
{
    heigthVerticalScrollBar = i;
    std::cout << "V: " << i << std::endl;
}

void DrawArea::scrollRelease(int i)
{
    widthHorizontalScrollBar = i;
    std::cout << "H: " << i << std::endl;
}

void DrawArea::drawLine( QPoint initial , QPoint final )
{
    scene->addItem( new Line( corrigeScrollPoint( initial ) , corrigeScrollPoint( final ) , scale ));
    scene->update();
}

void DrawArea::drawBezier( QPoint initial , QPoint control , QPoint final )
{
    scene->addItem( new Bezier( corrigeScrollPoint( initial ) , corrigeScrollPoint( control ) , corrigeScrollPoint( final ) , scale ) );
    scene->update();
}

void DrawArea::drawArc( QPoint center , QPoint initial , QPoint final )
{
    scene->addItem( new Arc( corrigeScrollPoint( center ) , corrigeScrollPoint( initial ) , corrigeScrollPoint( final ) , scale ) );
    scene->update();
}