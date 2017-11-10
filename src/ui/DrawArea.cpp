#include "DrawArea.h"
#include "Line.h"
#include "Bezier.h"
#include "Arc.h"

#include <iostream>
#include <QMouseEvent>
#include <QtMath>
#include <QScrollBar>

DrawArea::DrawArea( int _widthArea , int _heightArea ) : widthArea( _widthArea ) , heightArea( _heightArea ) , widthHorizontalScrollBar( 0 ) , heigthVerticalScrollBar( 0 ) , scale( 1 ) , scene( new QGraphicsScene( this ) ) , currentItem( nullptr ) , currentShape( LINE )
{
    setScene( scene );

    setBackgroundRole( QPalette::Base );
    setAutoFillBackground( true );
    setFixedSize( widthArea + 10 , heightArea + 10 );
    scene->setSceneRect( QRect( QPoint( 0 , 0 ) , QPoint( widthArea , heightArea ) ) );

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

    if ( scale <= 1 )
        setFixedSize( widthArea * scale + 10 , heightArea *scale + 10 );
    else 
        setFixedSize( widthArea + 10 , heightArea + 10 );
}

void DrawArea::mousePressEvent(QMouseEvent * event)
{
    if ( currentShape == SHAPE::LINE ) {
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

void DrawArea::mouseMoveEvent(QMouseEvent * event)
{
    QPoint p = event->pos();
    if (currentItem)
        delete currentItem;

    switch ( currentShape ) 
    {
    case LINE:       currentItem = new Line( corrigeScrollPoint( points[0] ) , corrigeScrollPoint( event->pos() ) , scale );                                                      break;
    case BEZIER:   currentItem = new Bezier( corrigeScrollPoint( points[0] ) , corrigeScrollPoint( points[1] ) , corrigeScrollPoint( event->pos() ) , scale );     break;
    case ARC:       currentItem = new Arc( corrigeScrollPoint( points[0] ) , corrigeScrollPoint( points[1] ) , corrigeScrollPoint( event->pos() ) , scale );          break;
    }

    scene->addItem(currentItem);
    scene->update();
    event->accept();
}

void DrawArea::mouseReleaseEvent(QMouseEvent * event)
{
    if ( currentShape == SHAPE::LINE ) {
        itens.push_back( currentItem );
        clearPoints();
    }
    else {
        if ( !points[1].isNull() ) {
            itens.push_back( currentItem );
            clearPoints();
        }
    }
    setMouseTracking( false );
}

bool DrawArea::eventFilter( QObject * o , QEvent * e )
{
    /*QEvent::Type t = e->type();
    if ( e->type() == QEvent::DynamicPropertyChange )
    {
        QSize s =  viewport()->size();
        QRectF s1 = scene->itemsBoundingRect();

        scene->update();
        QRectF qf = scene->sceneRect();

        int h = hScrollBar->pageStep();
        QRect h2 = hScrollBar->contentsRect();
        int max = hScrollBar->maximum();
        int min = hScrollBar->minimum();

        if ( ( s1.right() * scale ) > qreal( s.width() ) ) {
            setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            hScrollBar->setRange( 0 , ( s1.right() * scale ) );
        }

        if ( ( s1.bottom() * scale ) > qreal( s.height() ) ) {
            setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            vScrollBar->setRange( 0 , ( s1.bottom() * scale ) );
        }
    }*/
    return QAbstractScrollArea::eventFilter( o , e );
}

void DrawArea::clearPoints()
{
    currentItem = nullptr;
    points[0]=  points[1]= QPoint();
}

void DrawArea::setShapeToDraw( SHAPE shape )
{
    clearPoints();
    currentShape= shape;
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