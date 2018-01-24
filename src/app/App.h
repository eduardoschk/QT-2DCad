#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <QApplication>
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

   void startMoveXScroll(int value);
   void startMoveYScroll(int value);

   void startCommandDrawArc();
   void startCommandDrawLine();  
   void startCommandDrawBezier();

   void actionMousePressInDrawArea(Coordinate& coordinate);
   void actionMouseMoveInDrawArea(Coordinate& coordinate);
   void actionMouseReleaseInDrawArea(Coordinate& coordinate);

   void startCommandQuit();
   void startCommandNewFile();
   void startCommandOpenFile();
   void startCommandSaveFile();
   void startCommandSaveAsFile();

   void startCommandResizeWindow(Size& size);
   void startCommandZoomValueChange(int value);
};

#endif // INCLUDED_APP_H