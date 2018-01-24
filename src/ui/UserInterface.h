#pragma once
#pragma warning( disable : 4290 )  
#ifndef INCLUDED_USER_INTERFACE_H
#define INCLUDED_USER_INTERFACE_H

#include <deque>
#include <string>
#include <QWidget>
#include <exception>

#include "Size.h"
#include "Coordinate.h"
#include "MainWindow.h"

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

   class CancelNewFile : public std::exception { char const* what() const { return ""; } };

   void init();

   void markOffAllOptions();
   void markArcOptionAsSelected();
   void markLineOptionAsSelected();
   void markBezierOptionAsSelected();

   Size getSizeWindow();
   void setZoomScaleWidget(int value);

   void disableMouseTracking();
   void activateMouseTracking();

   void createDrawArea();

   void setTitleWindow(const char* name);
   void setTipMessage(const char* messageTip);

   void destructVerticalScrollBar();
   void destructHorizontalScrollBar();
   void setVerticalScrollBarPosition(int value);
   void setHorizontalScrollBarPosition(int value);
   void createVerticalScrollBar(int pageStep,int limit);
   void createHorizontalScrollBar(int pageStep,int limit);

   void clearArea();
   void eraseShape(int idShape);
   void drawCoordinate(int idShape,Coordinate coordinate);
   void drawCoordinates(int idShape,std::deque<Coordinate> coordinates);

   std::string showPopupNewFile() throw(CancelNewFile);

   std::string requestPathFileToOpen();
   void showErrorMessage(std::string message);
   bool confirmOperation(std::string message);
   std::string requestPathFileToSave(std::string fileName);

public slots:
   void startCreateArc();
   void startCreateLine();
   void startCreateBezier();

   void mouseMoveEventInDrawArea(Coordinate coordinate);
   void mousePressEventInDrawArea(Coordinate coordinate);
   void mouseReleaseEventInDrawArea(Coordinate coordinate);

   void verticalScrollMove(int value);
   void horizontalScrollMove(int value);

   void startOptionNewFile();
   void startOptionOpenFile();
   void startOptionSaveFile();
   void startOptionSaveAsFile();
   void startOptionQuit();

   void startResizeWindow(Size size);
   void startZoomValueChange(int value);
};

#endif // INCLUDED_USER_INTERFACE_H