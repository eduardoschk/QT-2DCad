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

   void actionMousePressInDrawArea(int x,int y);
   void actionMouseMoveInDrawArea(int x,int y);
   void actionMouseReleaseInDrawArea(int x,int y);

   void startCommandQuit();
   void startCommandNewFile();
   void startCommandOpenFile();
   void startCommandSaveFile();
   void startCommandSaveAsFile();

   void startCommandZoomValueChange(int value);
};

#endif // INCLUDED_APP_H