#pragma once
#ifndef INCLUDED_USER_INTERFACE_H
#define INCLUDED_USER_INTERFACE_H

#include <QWidget>
#include <string>
#include "MainWindow.h"
#include "NewFileStructure.h"

class App;

class UserInterface : public QWidget
{
   Q_OBJECT
private:
   MainWindow mainWindow;
   App& app;

public:
   ~UserInterface() {}
   UserInterface(App& _app,QWidget* parent= nullptr);

   void setTitleWindow(const char* name);
   void createDrawArea(int width,int height);

   void drawTempLine(int xInit,int yInit,int xFinal,int yFinal);
   void drawTempArc(int xCenter,int yCenter,int xInit,int yInit,int xFinal,int yFinal);
   void drawTempBezier(int xInit,int yInit,int xControl,int yControl,int xFinal,int yFinal);

   void drawLine(int xInit,int yInit,int xFinal,int yFinal);
   void drawArc(int xCenter,int yCenter,int xInit,int yInit,int xFinal,int yFinal);
   void drawBezier(int xInit,int yInit,int xControl,int yControl,int xFinal,int yFinal);

   void setDrawingScale(float scale);

   NEW_FILE_STRUCTURE showPopupNewFile();

   std::string requestPathFileToOpen();
   void showErrorMessage(std::string message);
   bool confirmOperation(std::string message);
   std::string requestPathFileToSave(std::string fileName);

public slots:
   void setShapeArc();
   void setShapeLine();
   void setShapeBezier();

   void mouseMoveEventInDrawArea(QPoint point);
   void mousePressEventInDrawArea(QPoint point);
   void mouseReleaseEventInDrawArea(QPoint point);

   void optionNewFile();
   void optionOpenFile();
   void optionSaveFile();
   void optionSaveAsFile();
   void optionQuit();

   void zoomValueChange(int value);
};

#endif // INCLUDED_USER_INTERFACE_H