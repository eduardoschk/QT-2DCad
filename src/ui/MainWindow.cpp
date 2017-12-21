#include "mainwindow.h"

#include <QSlider>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QCoreApplication>

#include "DrawArea.h"
#include "ZoomControl.h"
#include "NewDrawPopup.h"
#include "UserInterface.h"

int HEIGHT_ZOOM_WIDGET= 100;
int WIDTH_ZOOM_WIDGET= 30;

MainWindow::~MainWindow()
{
   if (drawArea)
      delete drawArea;
   delete qActionArc;
   delete qActionLine;
   delete qActionBezier;
   delete qSliderZoom;
}

MainWindow::MainWindow(UserInterface& _ui,QWidget* parent) : QMainWindow(parent),drawArea(nullptr),ui(_ui)
{
   setBackgroundRole(QPalette::Dark);
   setAutoFillBackground(true);

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

void MainWindow::createNewDrawArea(int _width,int _height)
{
   drawArea= new DrawArea(_width,_height,width(),height() - HEIGHT_ZOOM_WIDGET);
   configureDrawActions();
   setCentralWidget(drawArea);
   qSliderZoom->setValue(ZOOM::DEFAULT);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::drawLine(int id,QPoint initial,QPoint final)
{
   drawArea->drawLine(id,initial,final); 
}

void MainWindow::drawArc(int id,QPoint center,QPoint initial,QPoint final)
{ 
   drawArea->drawArc(id,center,initial,final); 
}

void MainWindow::drawBezier(int id,QPoint initial,QPoint control,QPoint final)
{ 
   drawArea->drawBezier(id,initial,control,final); 
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

void MainWindow::eraseDraw(int id)
{
   drawArea->eraseItem(id); 
}

///////////////////////////////////////////////////////////////////////////////

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
   qSliderZoom->setTickInterval(1);
   qSliderZoom->setFocusPolicy(Qt::StrongFocus);
   qSliderZoom->setTickPosition(QSlider::TicksBelow);

   QPushButton* zoomOut= new QPushButton(QIcon(":/zoom-out.png"),"",this);
   zoomOut->setFixedWidth(WIDTH_ZOOM_WIDGET);

   QPushButton* zoomIn= new QPushButton(QIcon(":/zoom-in.png"),"",this);
   zoomIn->setFixedWidth(WIDTH_ZOOM_WIDGET);

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
   connect(drawArea,SIGNAL(mouseMove(QPoint)),&ui,SLOT(mouseMoveEventInDrawArea(QPoint)));
   connect(drawArea,SIGNAL(mousePress(QPoint)),&ui,SLOT(mousePressEventInDrawArea(QPoint)));
   connect(drawArea,SIGNAL(mouseRelease(QPoint)),&ui,SLOT(mouseReleaseEventInDrawArea(QPoint)));
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
   if (drawArea)
      drawArea->setLimitArea(event->size());
}

void MainWindow::setDrawingScale(float scale) 
{
   drawArea->setScale(scale);
}