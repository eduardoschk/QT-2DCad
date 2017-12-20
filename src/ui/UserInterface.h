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
public:
   MainWindow mainWindow;
   App& app;

public:
   ~UserInterface() {}
   UserInterface(App& _app,QWidget* parent= nullptr) : QWidget(parent),app(_app),mainWindow(*this) {}

   void setShapeArc() { mainWindow.setShapArc(); }
   void setShapeLine() { mainWindow.setShapeLine(); }
   void setShapeBezier() { mainWindow.setShapeBezier(); }

   void setDrawingScale(float scale) { mainWindow.setDrawingScale(scale); }

   void setTitleWindow(const char* name) { mainWindow.setWindowTitle(name); }
   void createDrawArea(int width,int height) { mainWindow.createNewDrawArea(width,height); }

   void eraseDraw(int id) { mainWindow.eraseDraw(id); }

   void drawLine(int id,int xInit,int yInit,int xFinal,int yFinal) { mainWindow.drawLine(id,QPoint(xInit,yInit),QPoint(xFinal,yFinal)); }
   void drawArc(int id,int xCenter,int yCenter,int xInit,int yInit,int xFinal,int yFinal) { mainWindow.drawArc(id,QPoint(xCenter,yCenter),QPoint(xInit,yInit),QPoint(xFinal,yFinal)); }
   void drawBezier(int id,int xInit,int yInit,int xControl,int yControl,int xFinal,int yFinal) { mainWindow.drawBezier(id,QPoint(xInit,yInit),QPoint(xControl,yControl),QPoint(xFinal,yFinal)); }

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

   void optionNewFile();
   void optionOpenFile();
   void optionSaveFile();
   void optionSaveAsFile();
   void optionQuit();

   void zoomValueChange(int value);
};

#endif // INCLUDED_USER_INTERFACE_H