#include "App.h"
#include "UserInterface.h"
#include "Data.h"
#include "Command.h"
#include "CommandNew.h"
#include "CommandOpen.h"
#include "CommandSave.h"
#include "CommandSaveAs.h"
#include "CommandSetShapeArc.h"
#include "CommandSetShapeLine.h"
#include "CommandSetShapeBezier.h"
#include "CommandZoomValueChange.h"
#include "CommandMouseMoveInDrawArea.h"
#include "CommandMousePressInDrawArea.h"
#include "CommandMouseReleaseInDrawArea.h"

App::~App()
{
   setCurrentCmd(nullptr);
}


App::App(int argc,char **argv) : QApplication(argc,argv),userInterface(*this)
{
   currentCommand= nullptr;
}

///////////////////////////////////////////////////////////////////////////////

void App::run()
{
   exec();
   actionQuit();
}

///////////////////////////////////////////////////////////////////////////////

void App::setCurrentCmd(Command* newCm)
{
   if (currentCommand)
      delete currentCommand;

   currentCommand= newCm;

   if (currentCommand)
      currentCommand->exec(data,userInterface);
}

///////////////////////////////////////////////////////////////////////////////

void App::actionSetShapeArc()
{
   setCurrentCmd(new CommandSetShapeArc());
}

void App::actionSetShapeLine()
{
   setCurrentCmd(new CommandSetShapeLine());
}

void App::actionSetShapeBezier()
{
   setCurrentCmd(new CommandSetShapeBezier());
}

///////////////////////////////////////////////////////////////////////////////

void App::actionMousePressInDrawArea(int x,int y)
{
   setCurrentCmd(new CommandMousePressInDrawArea(Point(x,y)));
}

void App::actionMouseMoveInDrawArea(int x,int y)
{
   setCurrentCmd(new CommandMouseMoveInDrawArea(Point(x,y)));
}

void App::actionMouseReleaseInDrawArea(int x,int y)
{
   setCurrentCmd(new CommandMouseReleaseInDrawArea(Point(x,y)));
}

///////////////////////////////////////////////////////////////////////////////

void App::actionNewFile()
{
   setCurrentCmd(new CommandNew());
}

void App::actionOpenFile()
{
   setCurrentCmd(new CommandOpen());
}

void App::actionSaveFile()
{
   setCurrentCmd(new CommandSave());
}

void App::actionSaveAsFile()
{
   setCurrentCmd(new CommandSaveAs());
}

void App::actionQuit()
{
   quit();
}

void App::actionZoomValueChange(int value)
{
   setCurrentCmd(new CommandZoomValueChange(value));
}