#include "mainwindow.h"

#include <QSlider>
#include <QMenuBar>
#include <QToolBar>
#include <QScrollBar>
#include <QStatusBar>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QCoreApplication>

#include "Size.h"
#include "DrawArea.h"
#include "ZoomControl.h"
#include "UserInterface.h"

int HEIGHT_ZOOM_WIDGET= 105;
int WIDTH_ZOOM_BUTTON= 30;

MainWindow::~MainWindow()
{
   if (drawArea)
      delete drawArea;
   delete qActionArc;
   delete qActionLine;
   delete qActionBezier;
   delete qSliderZoom;
}

MainWindow::MainWindow(UserInterface& _ui,QWidget* parent) : QMainWindow(parent),drawArea(nullptr),verticalScroll(nullptr),horizontalScroll(nullptr),ui(_ui),viewPort(this)
{
   setAutoFillBackground(true);
   setBackgroundRole(QPalette::Dark);

   configureDrawArea();
   configureMenuBar(*menuBar());
   configureToolBarShapes();
   configureZoomControlOnStatusBar();

   showMaximized();
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::markOffAllOptions()
{
   qActionArc->setChecked(false);
   qActionLine->setChecked(false);
   qActionBezier->setChecked(false);
}

void MainWindow::markLineOptionAsSelected()
{
   markOffAllOptions();
   qActionLine->setChecked(true);
}

void MainWindow::markBezierOptionAsSelected()
{
   markOffAllOptions();
   qActionBezier->setChecked(true);
}

void MainWindow::markArcOptionAsSelected()
{
   markOffAllOptions();
   qActionArc->setChecked(true);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::createNewDrawArea()
{
   drawArea= new DrawArea(&viewPort);
   configureDrawActions();

   delete viewPort.layout();
   QGridLayout* layout= new QGridLayout(this);
   layout->setMargin(0);
   layout->addWidget(drawArea,0,0);

   viewPort.setLayout(layout);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::clearArea()
{
   drawArea->clearArea();
}

void MainWindow::eraseShape(int idShape)
{
   drawArea->eraseShape(idShape);
}

void MainWindow::drawPoint(int idShape,Point& point)
{
   drawArea->drawPoint(idShape,point);
}

void MainWindow::drawPoints(int idShape,std::deque<Point>& points)
{
   drawArea->drawPoints(idShape,points);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::activateMouseTracking()
{
   drawArea->setMouseTracking(true);
}

void MainWindow::disableMouseTracking()
{
   drawArea->setMouseTracking(false);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::configureDrawArea()
{
   setCentralWidget(&viewPort);
   QGridLayout* gridLayout= new QGridLayout(this);

   gridLayout->setMargin(0);
   gridLayout->addWidget(drawArea,0,0);
   
   viewPort.setLayout(gridLayout);
}

void MainWindow::configureMenuBar(QMenuBar& menu)
{
   QMenu* file= menu.addMenu("Arquivo");
   QAction* newAction= file->addAction("Novo");
   QAction* openAction= file->addAction("Abrir");
   QAction* saveAction= file->addAction("Salvar");
   QAction* saveAsAction= file->addAction("Salvar Como..");
   file->addSeparator();
   QAction* exitAction= file->addAction("Sair");


   connect(newAction,&QAction::triggered,&ui,&UserInterface::startOptionNewFile);
   connect(openAction,&QAction::triggered,&ui,&UserInterface::startOptionOpenFile);
   connect(saveAction,&QAction::triggered,&ui,&UserInterface::startOptionSaveFile);
   connect(saveAsAction,&QAction::triggered,&ui,&UserInterface::startOptionSaveAsFile);
   connect(exitAction,&QAction::triggered,&ui,&UserInterface::startOptionQuit);
}

void MainWindow::configureToolBarShapes()
{
   QToolBar* tool= new QToolBar(this);
   addToolBar(tool);
   qActionLine=   tool->addAction(QIcon(":/line.png"),"Linha");
   qActionBezier= tool->addAction(QIcon(":/bezier.png"),"Bezier");
   qActionArc=    tool->addAction(QIcon(":/arc.png"),"Arco");

   qActionArc->setCheckable(true);
   qActionLine->setCheckable(true);
   qActionBezier->setCheckable(true);

   connect(qActionArc,&QAction::triggered,&ui,&UserInterface::startCreateArc);
   connect(qActionLine,&QAction::triggered,&ui,&UserInterface::startCreateLine);
   connect(qActionBezier,&QAction::triggered,&ui,&UserInterface::startCreateBezier);
}

void MainWindow::configureZoomControlOnStatusBar()
{
   QWidget* zoomControl= new QWidget(this);
   QHBoxLayout* layoutZoomControl= new QHBoxLayout(this);

   qSliderZoom= new QSlider(Qt::Horizontal);
   qSliderZoom->setMinimum(ZOOM::FIRST);
   qSliderZoom->setMaximum(ZOOM::LAST);
   qSliderZoom->setValue(ZOOM::DEFAULT);
   qSliderZoom->setFocusPolicy(Qt::StrongFocus);
   qSliderZoom->setTickPosition(QSlider::TicksBelow);

   QPushButton* zoomOut= new QPushButton(QIcon(":/zoom-out.png"),"",this);
   zoomOut->setFixedWidth(WIDTH_ZOOM_BUTTON);

   QPushButton* zoomIn= new QPushButton(QIcon(":/zoom-in.png"),"",this);
   zoomIn->setFixedWidth(WIDTH_ZOOM_BUTTON);

   layoutZoomControl->addWidget(zoomOut);
   layoutZoomControl->addWidget(qSliderZoom);
   layoutZoomControl->addWidget(zoomIn);

   zoomControl->setLayout(layoutZoomControl);

   QStatusBar* status= statusBar();
   status->addPermanentWidget(zoomControl);

   connect(zoomOut,SIGNAL(pressed()),this,SLOT(minusZoomClicked()));
   connect(zoomIn,SIGNAL(pressed()),this,SLOT(plusZoomClicked()));
   connect(qSliderZoom,SIGNAL(valueChanged(int)),&ui,SLOT(startZoomValueChange(int)));
}

void MainWindow::configureDrawActions()
{
   connect(drawArea,SIGNAL(mouseMove(Point)),&ui,SLOT(mouseMoveEventInDrawArea(Point)));
   connect(drawArea,SIGNAL(mousePress(Point)),&ui,SLOT(mousePressEventInDrawArea(Point)));
   connect(drawArea,SIGNAL(mouseRelease(Point)),&ui,SLOT(mouseReleaseEventInDrawArea(Point)));
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::minusZoomClicked() 
{ 
   qSliderZoom->setValue(qSliderZoom->value() - 1); 
}

void MainWindow::plusZoomClicked() 
{ 
   qSliderZoom->setValue(qSliderZoom->value() + 1);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::resizeEvent(QResizeEvent* event)
{
   ui.startResizeWindow(Size(event->size().width(),event->size().height()));
}

QSize MainWindow::getSizeWindow()
{
   return size();
}

void MainWindow::setZoomScaleWidget(int value)
{
   qSliderZoom->setValue(value);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::destructVerticalScrollBar()
{
   if (verticalScroll) {
      delete verticalScroll;
      verticalScroll= nullptr;
   }
}

void MainWindow::destructHorizontalScrollBar()
{
   if (horizontalScroll) {
      delete horizontalScroll;
      horizontalScroll= nullptr;
   }
}

void MainWindow::setVerticalScrollBarPosition(int value)
{
   if (verticalScroll)
      verticalScroll->setValue(value);
}

void MainWindow::setHorizontalScrollBarPosition(int value)
{
   if (horizontalScroll)
      horizontalScroll->setValue(value);
}

void MainWindow::createVerticalScrollBar(int pageStep,int limit)
{
   if (!verticalScroll) {
      verticalScroll= new QScrollBar(Qt::Vertical,&viewPort);
      QGridLayout* layout= dynamic_cast<QGridLayout*>(viewPort.layout());
      
      layout->addWidget(verticalScroll,0,1);
      connect(verticalScroll,SIGNAL(valueChanged(int)),&ui,SLOT(verticalScrollMove(int)));
   }
   
   verticalScroll->setMaximum(limit);
   verticalScroll->setPageStep(pageStep);
}

void MainWindow::createHorizontalScrollBar(int pageStep,int limit)
{
   if (!horizontalScroll) {
      horizontalScroll= new QScrollBar(Qt::Horizontal,&viewPort);
      QGridLayout* layout= dynamic_cast<QGridLayout*>(viewPort.layout());

      layout->addWidget(horizontalScroll,1,0);
      connect(horizontalScroll,SIGNAL(valueChanged(int)),&ui,SLOT(horizontalScrollMove(int)));
   }

   horizontalScroll->setMaximum(limit);
   horizontalScroll->setPageStep(pageStep);
}