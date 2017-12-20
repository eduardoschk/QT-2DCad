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
   delete arc;
   delete line;
   delete bezier;
   delete sliderZoom;
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

void MainWindow::setShapeLine()
{
   line->setChecked(true);
   arc->setChecked(false);
   bezier->setChecked(false);
}

void MainWindow::setShapeBezier()
{
   arc->setChecked(false);
   line->setChecked(false);
   bezier->setChecked(true);
}

void MainWindow::setShapArc()
{
   arc->setChecked(true);
   line->setChecked(false);
   bezier->setChecked(false);
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::createNewDrawArea(int _width,int _height)
{
   drawArea= new DrawArea(_width,_height,width(),height() - HEIGHT_ZOOM_WIDGET);
   configureDrawActions();
   setCentralWidget(drawArea);
   sliderZoom->setValue(ZOOM::DEFAULT);
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

void MainWindow::eraseDraw(int id)
{
   drawArea->eraseItem(id); 
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::configureMenuBar(QMenuBar& menu)
{
   QMenu* arquivo= menu.addMenu("Arquivo");
   QAction* newAction= arquivo->addAction("Novo");
   QAction* openAction= arquivo->addAction("Abrir");
   QAction* saveAction= arquivo->addAction("Salvar");
   QAction* saveAsAction= arquivo->addAction("Salvar Como..");
   arquivo->addSeparator();
   QAction* exitAction= arquivo->addAction("Sair");


   connect(newAction,&QAction::triggered,&ui,&UserInterface::optionNewFile);
   connect(openAction,&QAction::triggered,&ui,&UserInterface::optionOpenFile);
   connect(saveAction,&QAction::triggered,&ui,&UserInterface::optionSaveFile);
   connect(saveAsAction,&QAction::triggered,&ui,&UserInterface::optionSaveAsFile);
   connect(exitAction,&QAction::triggered,&ui,&UserInterface::optionQuit);
}

void MainWindow::configureToolBarShapes()
{
   QToolBar* tool= new QToolBar(this);
   addToolBar(tool);
   line=   tool->addAction(QIcon(":/line.png"),"Linha");
   bezier= tool->addAction(QIcon(":/bezier.png"),"Bezier");
   arc=    tool->addAction(QIcon(":/arc.png"),"Arco");

   arc->setCheckable(true);
   line->setCheckable(true);
   bezier->setCheckable(true);

   connect(arc,&QAction::triggered,&ui,&UserInterface::startCreateArc);
   connect(line,&QAction::triggered,&ui,&UserInterface::startCreateLine);
   connect(bezier,&QAction::triggered,&ui,&UserInterface::startCreateBezier);
}

void MainWindow::configureZoomControlOnStatusBar()
{
   QWidget* zoomControl= new QWidget(this);
   QHBoxLayout* layoutZoomControl= new QHBoxLayout(this);

   sliderZoom= new QSlider(Qt::Horizontal);
   sliderZoom->setMinimum(ZOOM::FIRST);
   sliderZoom->setMaximum(ZOOM::LAST);
   sliderZoom->setValue(ZOOM::DEFAULT);
   sliderZoom->setTickInterval(1);
   sliderZoom->setFocusPolicy(Qt::StrongFocus);
   sliderZoom->setTickPosition(QSlider::TicksBelow);

   QPushButton* zoomOut= new QPushButton(QIcon(":/zoom-out.png"),"",this);
   zoomOut->setFixedWidth(WIDTH_ZOOM_WIDGET);

   QPushButton* zoomIn= new QPushButton(QIcon(":/zoom-in.png"),"",this);
   zoomIn->setFixedWidth(WIDTH_ZOOM_WIDGET);

   layoutZoomControl->addWidget(zoomOut);
   layoutZoomControl->addWidget(sliderZoom);
   layoutZoomControl->addWidget(zoomIn);

   zoomControl->setLayout(layoutZoomControl);

   QStatusBar* status= statusBar();
   status->addPermanentWidget(zoomControl);

   connect(zoomOut,SIGNAL(pressed()),this,SLOT(minusZoomClicked()));
   connect(zoomIn,SIGNAL(pressed()),this,SLOT(plusZoomClicked()));
   connect(sliderZoom,SIGNAL(valueChanged(int)),&ui,SLOT(zoomValueChange(int)));
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
   sliderZoom->setValue(sliderZoom->value() - 1); 
}

void MainWindow::plusZoomClicked() 
{ 
   sliderZoom->setValue(sliderZoom->value() + 1); 
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