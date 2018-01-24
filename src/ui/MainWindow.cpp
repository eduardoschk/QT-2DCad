#include "mainwindow.h"

#include <QLabel>
#include <QSlider>
#include <QMenuBar>
#include <QToolBar>
#include <QScrollBar>
#include <QStatusBar>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QResizeEvent>

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
   delete qLTipMessage;
}

MainWindow::MainWindow(UserInterface& _ui,QWidget* parent) : QMainWindow(parent),drawArea(nullptr),verticalScroll(nullptr),horizontalScroll(nullptr),ui(_ui),viewPort(this)
{
   setAutoFillBackground(true);
   setBackgroundRole(QPalette::Shadow);

   setCentralWidget(&viewPort);
   configureMenuBar(*menuBar());
   configureToolBarShapes();
   configureZoomControlOnStatusBar();

   showMaximized();
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::configureMenuBar(QMenuBar& menu)
{
   QMenu* file= menu.addMenu("File");
   QAction* newAction= file->addAction("New");
   QAction* openAction= file->addAction("Open");
   QAction* saveAction= file->addAction("Save");
   QAction* saveAsAction= file->addAction("Save As..");
   file->addSeparator();
   QAction* exitAction= file->addAction("Exit");

   newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
   openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
   saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
   saveAsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));

   connect(newAction,&QAction::triggered,&ui,&UserInterface::startOptionNewFile);
   connect(openAction,&QAction::triggered,&ui,&UserInterface::startOptionOpenFile);
   connect(saveAction,&QAction::triggered,&ui,&UserInterface::startOptionSaveFile);
   connect(saveAsAction,&QAction::triggered,&ui,&UserInterface::startOptionSaveAsFile);
   connect(exitAction,&QAction::triggered,&ui,&UserInterface::startOptionQuit);
}

void MainWindow::configureToolBarShapes()
{
   QToolBar* tool= new QToolBar(this);
   tool->setAutoFillBackground(true);
   tool->setBackgroundRole(QPalette::Mid);

   addToolBar(tool);
   qActionLine=   tool->addAction(QIcon(":/line.png"),"Line");
   qActionBezier= tool->addAction(QIcon(":/bezier.png"),"Bezier");
   qActionArc=    tool->addAction(QIcon(":/arc.png"),"Arc");

   qActionLine->setShortcut(QKeySequence(Qt::Key_F1));
   qActionBezier->setShortcut(QKeySequence(Qt::Key_F2));
   qActionArc->setShortcut(QKeySequence(Qt::Key_F3));

   qActionArc->setCheckable(true);
   qActionLine->setCheckable(true);
   qActionBezier->setCheckable(true);

   connect(qActionArc,&QAction::triggered,&ui,&UserInterface::startCreateArc);
   connect(qActionLine,&QAction::triggered,&ui,&UserInterface::startCreateLine);
   connect(qActionBezier,&QAction::triggered,&ui,&UserInterface::startCreateBezier);
}

void MainWindow::configureZoomControlOnStatusBar()
{
   qLTipMessage= new QLabel();
   QWidget* zoomControl= new QWidget(this);
   QHBoxLayout* layoutZoomControl= new QHBoxLayout(zoomControl);

   qSliderZoom= new QSlider(Qt::Horizontal);
   qSliderZoom->setMinimum(ZOOM::FIRST);
   qSliderZoom->setMaximum(ZOOM::LAST);
   qSliderZoom->setValue(ZOOM::DEFAULT);
   qSliderZoom->setFocusPolicy(Qt::StrongFocus);
   qSliderZoom->setTickPosition(QSlider::TicksBelow);

   QPushButton* zoomOut= new QPushButton(QIcon(":/zoom-out.png"),"",this);
   zoomOut->setFixedWidth(WIDTH_ZOOM_BUTTON);
   zoomOut->setShortcut(QKeySequence(Qt::Key_Minus));

   QPushButton* zoomIn= new QPushButton(QIcon(":/zoom-in.png"),"",this);
   zoomIn->setFixedWidth(WIDTH_ZOOM_BUTTON);
   zoomIn->setShortcut(QKeySequence(Qt::Key_Plus));

   layoutZoomControl->addWidget(zoomOut);
   layoutZoomControl->addWidget(qSliderZoom);
   layoutZoomControl->addWidget(zoomIn);

   zoomControl->setLayout(layoutZoomControl);

   QStatusBar* status= statusBar();
   status->setAutoFillBackground(true);
   status->setBackgroundRole(QPalette::Mid);

   status->addWidget(qLTipMessage);
   status->addPermanentWidget(zoomControl);

   connect(zoomOut,SIGNAL(pressed()),this,SLOT(minusZoomClicked()));
   connect(zoomIn,SIGNAL(pressed()),this,SLOT(plusZoomClicked()));
   connect(qSliderZoom,SIGNAL(valueChanged(int)),&ui,SLOT(startZoomValueChange(int)));
}

void MainWindow::configureDrawActions()
{
   connect(drawArea,SIGNAL(mouseMove(Coordinate)),&ui,SLOT(mouseMoveEventInDrawArea(Coordinate)));
   connect(drawArea,SIGNAL(mousePress(Coordinate)),&ui,SLOT(mousePressEventInDrawArea(Coordinate)));
   connect(drawArea,SIGNAL(mouseRelease(Coordinate)),&ui,SLOT(mouseReleaseEventInDrawArea(Coordinate)));
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

void MainWindow::setTipMessage(const char* messageTip)
{
   qLTipMessage->setText(QString::fromLatin1(messageTip));
}

///////////////////////////////////////////////////////////////////////////////

void MainWindow::createNewDrawArea()
{
   drawArea= new DrawArea(&viewPort);
   configureDrawActions();

   delete viewPort.layout();
   QGridLayout* layout= new QGridLayout();
   layout->setMargin(0);
   layout->addWidget(drawArea,0,0);

   viewPort.setLayout(layout);
}

void MainWindow::clearArea()
{
   drawArea->clearArea();
}

void MainWindow::eraseShape(int idShape)
{
   drawArea->eraseShape(idShape);
}

void MainWindow::drawCoordinate(int idShape,Coordinate& coordinate)
{
   drawArea->drawCoordinate(idShape,coordinate);
}

void MainWindow::drawCoordinates(int idShape,std::deque<Coordinate>& coordinates)
{
   drawArea->drawCoordinates(idShape,coordinates);
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