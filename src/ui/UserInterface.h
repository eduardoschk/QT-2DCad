#pragma once
#ifndef INCLUDED_USER_INTERFACE_H
#define INCLUDED_USER_INTERFACE_H

#include <QWidget>
#include <deque>
#include <string>
#include "Size.h"
#include "Point.h"
#include "MainWindow.h"
#include "NewFileStructure.h"

class App;

class UserInterface : public QWidget
{
   Q_OBJECT
private:
   App& app;
   bool initialized;
   MainWindow mainWindow;

public:
   ~UserInterface() {}
   UserInterface(App& _app);

   void init();

   void markOffAllOptions();
   void markArcOptionAsSelected();
   void markLineOptionAsSelected();
   void markBezierOptionAsSelected();

   Size getSizeWindow();
   void setSizeViewPort(Size size);
   void setSizeDrawArea(Size size);
   void setZoomScaleWidget(int value);

   void disableMouseTracking();
   void activateMouseTracking();

   void createDrawArea(Size size);
   void setTitleWindow(const char* name);

   void destructVerticalScrollBar();
   void destructHorizontalScrollBar();
   void setVerticalScrollBarPosition(int value);
   void setHorizontalScrollBarPosition(int value);
   void createVerticalScrollBar(int pageStep,int limit);
   void createHorizontalScrollBar(int pageStep,int limit);

   void clearArea();
   void eraseShape(int idShape);
   void drawPoint(int idShape,Point point);
   void drawPoints(int idShape,std::deque<Point> points);

   NEW_FILE_STRUCTURE showPopupNewFile();

   std::string requestPathFileToOpen();
   void showErrorMessage(std::string message);
   bool confirmOperation(std::string message);
   std::string requestPathFileToSave(std::string fileName);

public slots:
   void startCreateArc();
   void startCreateLine();
   void startCreateBezier();

   void mouseMoveEventInDrawArea(QPoint point);
   void mousePressEventInDrawArea(QPoint point);
   void mouseReleaseEventInDrawArea(QPoint point);

   void verticalScrollMove(int value);
   void horizontalScrollMove(int value);

   void startOptionNewFile();
   void startOptionOpenFile();
   void startOptionSaveFile();
   void startOptionSaveAsFile();
   void startOptionQuit();

   void startResizeWindow(QSize size);
   void startZoomValueChange(int value);
};

#endif // INCLUDED_USER_INTERFACE_H