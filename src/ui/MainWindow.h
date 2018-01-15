#pragma once
#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <QMainWindow>

class QLabel;
class QSlider;
class DrawArea;
class QScrollBar;
class UserInterface;

class MainWindow : public QMainWindow
{
   Q_OBJECT
private:
   UserInterface& ui;
   QWidget viewPort;
   DrawArea* drawArea;
   QScrollBar* verticalScroll;
   QScrollBar* horizontalScroll;

   QAction* qActionArc;
   QAction* qActionLine;
   QAction* qActionBezier;
   QSlider* qSliderZoom;

   void configureDrawArea();
   void configureDrawActions();
   void configureToolBarShapes();
   void configureZoomControlOnStatusBar();
   void configureMenuBar(QMenuBar& menuBar);
   void resizeEvent(QResizeEvent* event) override;

public:
   ~MainWindow();
   MainWindow(UserInterface& _ui,QWidget* parent= nullptr);

   void createNewDrawArea(QSize size);

   void activateMouseTracking();
   void disableMouseTracking();

   void clearArea();
   void eraseShape(int idShape);
   void drawPoint(int idShape,QPoint point);
   void drawPoints(int idShape,std::vector<QPoint> points);

   void markOffAllOptions();
   void markArcOptionAsSelected();
   void markLineOptionAsSelected();
   void markBezierOptionAsSelected();

   QSize getSizeWindow();
   void setSizeViewPort(QSize size);
   void setSizeDrawArea(QSize size);
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