#include "mainwindow.h"
#include "DrawArea.h"
#include "NewDrawPopup.h"

#include <QMenuBar>
#include <QToolBar>
#include <QSlider>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCoreApplication>

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
    INITIAL = FOUR
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), drawArea(nullptr)
{
    setBackgroundRole( QPalette::Dark );
    setAutoFillBackground( true );

    QMenuBar * menu = menuBar();
    QMenu * arquivo = menu->addMenu("Arquivo");
    QAction * newAction = arquivo->addAction( "Novo" );
     QAction * openAction = arquivo->addAction( "Abrir" );
     QAction * saveAction = arquivo->addAction( "Salvar" );
     QAction * saveAsAction = arquivo->addAction( "Salvar Como.." );
     arquivo->addSeparator();
     QAction * exitAction = arquivo->addAction( "Sair" );

    QToolBar * tool = new QToolBar();
    addToolBar( tool );
    QAction * line = tool->addAction( QIcon("C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/line.png") ,"Linha" );
    QAction * bezier = tool->addAction( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/bezier.png" ),"Bezier" );
    QAction * arc = tool->addAction( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/arc.png" ), "Arco" );

    line->setCheckable( true );
    bezier->setCheckable( true );
    arc->setCheckable( true );
    line->setChecked( true );

    QWidget * zoomControl = new QWidget();
    QHBoxLayout * layoutZoomControl = new QHBoxLayout();

    QPushButton * zoomOut = new QPushButton( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/zoom-out.png" ) , "");
    zoomOut->setFixedWidth(30);

    sliderZoom = new QSlider(Qt::Horizontal);
    sliderZoom->setMinimum( FIRST );
    sliderZoom->setMaximum( LAST );
    sliderZoom->setValue( INITIAL );
    sliderZoom->setTickInterval(1);
    sliderZoom->setFocusPolicy( Qt::StrongFocus );
    sliderZoom->setTickPosition( QSlider::TicksBelow );

    QPushButton * zoomIn= new QPushButton( QIcon( "C:/Users/eduardo.kreuch/Documents/Exercise 7 - CAD/img/icons/zoom-in.png" ), "" );
    zoomIn->setFixedWidth( 30 );

    layoutZoomControl->addWidget( zoomOut );
    layoutZoomControl->addWidget( sliderZoom );
    layoutZoomControl->addWidget( zoomIn );
    
    zoomControl->setLayout( layoutZoomControl );

    QStatusBar * status = statusBar();
    status->addPermanentWidget( zoomControl );

    showMaximized();

    connect( zoomOut, SIGNAL( pressed() ), this, SLOT( minusZoomClicked() ) );
    connect( zoomIn , SIGNAL( pressed() ) , this , SLOT( plusZoomClicked() ) );
    connect( sliderZoom , SIGNAL( valueChanged( int )), this,  SLOT( zoomValueChange( int )));

    connect( newAction , &QAction::triggered , this , &MainWindow::optionNewArchive );
    connect( exitAction , &QAction::triggered , this , &QCoreApplication::quit );
}

void MainWindow::minusZoomClicked()
{
    sliderZoom->setValue( sliderZoom->value() - 1);
}

void MainWindow::plusZoomClicked()
{
    sliderZoom->setValue( sliderZoom->value() + 1);
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

void MainWindow::optionNewArchive()
{
    NewDrawPopup *ndp = new NewDrawPopup();
    connect( ndp , SIGNAL( createNewArchive( QString , int , int ) ), this, SLOT( createNewArchive( QString , int , int ) ));
    ndp->show();
}

void MainWindow::createNewArchive( QString name , int width , int height )
{
    sliderZoom->setValue( INITIAL );
    drawArea= new DrawArea(width, height);
    setCentralWidget(drawArea);
}