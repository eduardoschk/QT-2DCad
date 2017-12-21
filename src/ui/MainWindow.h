#pragma once
#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <string.h>
#include <QMainWindow>

class QLabel;
class QSlider;
class DrawArea;
class UserInterface;

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   UserInterface& ui;
   DrawArea* drawArea;

   QAction* qActionArc;
   QAction* qActionLine;
   QAction* qActionBezier;
   QSlider* qSliderZoom;

   void configureDrawActions();
   void configureToolBarShapes();
   void configureZoomControlOnStatusBar();
   void configureMenuBar(QMenuBar& menuBar);
   void resizeEvent(QResizeEvent* event) override;

public:
   ~MainWindow();
   MainWindow(UserInterface& _ui,QWidget* parent= nullptr);

   void createNewDrawArea(int _width,int _heigth);

   void activateMouseTracking();
   void disableMouseTracking();

   void eraseDraw(int id);

   void drawLine(int id,QPoint initial,QPoint final);
   void drawArc(int id,QPoint center,QPoint initial,QPoint final);
   void drawBezier(int id,QPoint initial,QPoint control,QPoint final);

   void markOffAllOptions();
   void markArcOptionAsSelected();
   void markLineOptionAsSelected();
   void markBezierOptionAsSelected();

   void setDrawingScale(float scale);

public slots:
   void minusZoomClicked();
   void plusZoomClicked();
};

#endif // INCLUDED_MAIN_WINDOW_H