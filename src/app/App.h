#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <QApplication>
#include <string>

#include "Data.h"
#include "UserInterface.h"

class Command;

class App : public QApplication
{
private:
   Data data;
   Command* currentCommand;
   UserInterface userInterface;

   void setCurrentCmd(Command* newCm);

public:
   ~App();
   App(int argc,char **argv);

   void run();

   void startCommandDrawArc();
   void startCommandDrawLine();  
   void startCommandDrawBezier();

   void actionMousePressInDrawArea(Point point);
   void actionMouseMoveInDrawArea(Point point);
   void actionMouseReleaseInDrawArea(Point point);

   void startCommandQuit();
   void startCommandNewFile();
   void startCommandOpenFile();
   void startCommandSaveFile();
   void startCommandSaveAsFile();

   void startCommandZoomValueChange(int value);
   void startCommandResizeWindow(int height,int width);
};

#endif // INCLUDED_APP_H