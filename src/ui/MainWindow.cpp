#include "mainwindow.h"
#include "DrawArea.h"
#include "NewDrawPopup.h"
#include "UserInterface.h"

#include <QMenuBar>
#include <QToolBar>
#include <QSlider>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCoreApplication>
#include <QResizeEvent>

#include <iostream>

enum ZOOM {
    ONE = 1,
    TWO ,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE ,
    TEN ,
    FIRST = ONE,
    LAST = TEN,
    DEFAULT = FOUR
};

MainWindow::MainWindow( UserInterface * _owner , QWidget *parent )
    : QMainWindow( parent ) , drawArea( nullptr ), owner(_owner)
{
    setBackgroundRole( QPalette::Dark );
    setAutoFillBackground( true );

    configureMenuBar( *menuBar() );
    configureToolBarShapes();
    configureZoomControlOnStatusBar();

    showMaximized();
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::drawLine( QPoint initial , QPoint final )
{
    drawArea->drawLine( initial , final );
}

void MainWindow::drawBezier( QPoint initial , QPoint control , QPoint final )
{
    drawArea->drawBezier( initial , control , final );
}

void MainWindow::drawArc( QPoint center , QPoint initial , QPoint final )
{
    drawArea->drawArc( center , initial , final );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::setShapeLine()
{
    if (drawArea )
        drawArea->setShapeToDraw( LINE );
    bezier->setChecked( false );
    arc->setChecked( false );
}

void MainWindow::setShapeBezier()
{
    if ( drawArea )
        drawArea->setShapeToDraw( BEZIER );
    line->setChecked( false );
    arc->setChecked( false );
}

void MainWindow::setShapArc()
{
    if ( drawArea )
        drawArea->setShapeToDraw( ARC );
    bezier->setChecked( false );
    line->setChecked( false );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::minusZoomClicked()
{
    sliderZoom->setValue( sliderZoom->value() - 1);
}

void MainWindow::plusZoomClicked()
{
    sliderZoom->setValue( sliderZoom->value() + 1 );
}

void MainWindow::zoomValueChange( int value )
{
    if ( !drawArea )
        return;

    float scale;

    switch ( value ) {
    case ONE:   scale= 0.125;   break;
    case TWO:   scale= 0.25;    break;
    case THREE: scale= 0.5;     break;
    case FOUR:  scale= 1;       break;
    case FIVE:  scale= 2;       break;
    case SIX:   scale= 3;       break;
    case SEVEN: scale= 4;       break;
    case EIGHT: scale= 5;       break;
    case NINE:  scale= 6;       break;
    case TEN:   scale= 8;       break;
    }

    drawArea->setScale( scale );
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::createNewDrawArea( int _width , int _height )
{
    sliderZoom->setValue( DEFAULT );
    drawArea= new DrawArea( _width , _height , width() , height() - 100 );
    setCentralWidget( drawArea );
    configureDrawActions();
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::configureMenuBar( QMenuBar & menu )
{
    QMenu * arquivo = menu.addMenu( "Arquivo" );
    QAction * newAction = arquivo->addAction( "Novo" );
    QAction * openAction = arquivo->addAction( "Abrir" );
    QAction * saveAction = arquivo->addAction( "Salvar" );
    QAction * saveAsAction = arquivo->addAction( "Salvar Como.." );
    arquivo->addSeparator();
    QAction * exitAction = arquivo->addAction( "Sair" );


    connect( newAction , &QAction::triggered , owner , &UserInterface::optionNewFile );
    connect( openAction , &QAction::triggered , owner , &UserInterface::optionOpenFile );
    connect( saveAction , &QAction::triggered , owner , &UserInterface::optionSaveFile );
    connect( saveAsAction , &QAction::triggered , owner , &UserInterface::optionSaveAsFile );
    connect( exitAction , &QAction::triggered , owner , &UserInterface::optionQuit );
}

void MainWindow::configureToolBarShapes()
{
    QToolBar * tool = new QToolBar();
    addToolBar( tool );
    line =   tool->addAction( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/line.png" ) , "Linha" );
    bezier = tool->addAction( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/bezier.png" ) , "Bezier" );
    arc =    tool->addAction( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/arc.png" ) , "Arco" );

    line->setCheckable( true );
    bezier->setCheckable( true );
    arc->setCheckable( true );
    line->setChecked( true );

    connect( line , &QAction::triggered , this , &MainWindow::setShapeLine );
    connect( bezier , &QAction::triggered , this , &MainWindow::setShapeBezier );
    connect( arc , &QAction::triggered , this , &MainWindow::setShapArc );
}

void MainWindow::configureZoomControlOnStatusBar()
{
    QWidget * zoomControl = new QWidget();
    QHBoxLayout * layoutZoomControl = new QHBoxLayout();

    QPushButton * zoomOut = new QPushButton( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/zoom-out.png" ) , "" );
    zoomOut->setFixedWidth( 30 );

    sliderZoom = new QSlider( Qt::Horizontal );
    sliderZoom->setMinimum( FIRST );
    sliderZoom->setMaximum( LAST );
    sliderZoom->setValue( DEFAULT );
    sliderZoom->setTickInterval( 1 );
    sliderZoom->setFocusPolicy( Qt::StrongFocus );
    sliderZoom->setTickPosition( QSlider::TicksBelow );

    QPushButton * zoomIn= new QPushButton( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/zoom-in.png" ) , "" );
    zoomIn->setFixedWidth( 30 );

    layoutZoomControl->addWidget( zoomOut );
    layoutZoomControl->addWidget( sliderZoom );
    layoutZoomControl->addWidget( zoomIn );

    zoomControl->setLayout( layoutZoomControl );

    QStatusBar * status = statusBar();
    status->addPermanentWidget( zoomControl );


    connect( zoomOut , SIGNAL( pressed() ) , this , SLOT( minusZoomClicked() ) );
    connect( zoomIn , SIGNAL( pressed() ) , this , SLOT( plusZoomClicked() ) );
    connect( sliderZoom , SIGNAL( valueChanged( int ) ) , this , SLOT( zoomValueChange( int ) ) );
}

void MainWindow::configureDrawActions()
{
    connect( drawArea , SIGNAL( drawLineFinish( QPoint , QPoint )) , owner , SLOT( drawLineFinish( QPoint , QPoint )));
    connect( drawArea , SIGNAL( drawBezierFinish( QPoint , QPoint , QPoint )) , owner , SLOT( drawBezierFinish( QPoint , QPoint , QPoint )));
    connect( drawArea , SIGNAL( drawArcFinish( QPoint , QPoint , QPoint )) , owner , SLOT( drawArcFinish( QPoint , QPoint , QPoint )));
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::resizeEvent( QResizeEvent * event )
{
    if ( drawArea )
        drawArea->setLimitArea(event->size());
}