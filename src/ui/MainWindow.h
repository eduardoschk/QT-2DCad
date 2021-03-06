#pragma once
#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <QMainWindow>
#include <deque>
#include "Coordinate.h"

class QLabel;
class QSlider;
class DrawArea;
class QScrollBar;
class UserInterface;

class MainWindow : public QMainWindow
{
   Q_OBJECT
private:
   UserInterface & ui;
   QWidget viewPort;
   DrawArea* drawArea;
   QScrollBar* verticalScroll;
   QScrollBar* horizontalScroll;

   QAction* qActionArc;
   QAction* qActionLine;
   QAction* qActionBezier;
   QSlider* qSliderZoom;

   QLabel* qLTipMessage;

   void configureDrawActions();
   void configureToolBarShapes();
   void configureZoomControlOnStatusBar();
   void configureMenuBar(QMenuBar& menuBar);
   void resizeEvent(QResizeEvent* event) override;

public:
   ~MainWindow();
   MainWindow(UserInterface& _ui,QWidget* parent= nullptr);

   void createNewDrawArea();
   void setTipMessage(const char* messageTip);

   void activateMouseTracking();
   void disableMouseTracking();

   void clearArea();
   void eraseShape(int idShape);
   void drawCoordinate(int idShape,Coordinate& coordinate);
   void drawCoordinates(int idShape,std::deque<Coordinate>& coordinates);

   void markOffAllOptions();
   void markArcOptionAsSelected();
   void markLineOptionAsSelected();
   void markBezierOptionAsSelected();

   QSize getSizeWindow();
   void setZoomScaleWidget(int value);

   void destructVerticalScrollBar();
   void destructHorizontalScrollBar();
   void setVerticalScrollBarPosition(int value);
   void setHorizontalScrollBarPosition(int value);
   void createVerticalScrollBar(int pageStep,int limit);
   void createHorizontalScrollBar(int pagetStep,int limit);

   public slots:
   void minusZoomClicked();
   void plusZoomClicked();

};

#endif // INCLUDED_MAIN_WINDOW_H