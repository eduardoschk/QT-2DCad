#pragma once
#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <QMainWindow>
#include <string.h>

class DrawArea;
class QSlider;
class QLabel;
class UserInterface;

class MainWindow : public QMainWindow
{
   Q_OBJECT
private:
   UserInterface& ui;
   DrawArea* drawArea;

   QAction* line;
   QAction* bezier;
   QAction* arc;
   QSlider* sliderZoom;

   void configureDrawActions();
   void configureToolBarShapes();
   void configureZoomControlOnStatusBar();
   void configureMenuBar(QMenuBar& menuBar);
   void resizeEvent(QResizeEvent* event) override;

public:
   ~MainWindow();
   MainWindow(UserInterface& _ui,QWidget* parent= nullptr);

   void createNewDrawArea(int _width,int _heigth);

   void drawTempLine(QPoint initial,QPoint final);
   void drawTempArc(QPoint center,QPoint initial,QPoint final);
   void drawTempBezier(QPoint initial,QPoint control,QPoint final);

   void drawLine(QPoint initial,QPoint final);
   void drawArc(QPoint center,QPoint initial,QPoint final);
   void drawBezier(QPoint initial,QPoint control,QPoint final);

   void setShapArc();
   void setShapeLine();
   void setShapeBezier();

   void setDrawingScale(float scale);

public slots:
   void minusZoomClicked();
   void plusZoomClicked();
};

#endif // INCLUDED_MAIN_WINDOW_H