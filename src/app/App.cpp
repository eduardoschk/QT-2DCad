#include "App.h"
#include "Data.h"
#include "UserInterface.h"
#include "Command.h"
#include "CommandNew.h"
#include "CommandOpen.h"
#include "CommandSave.h"
#include "CommandSaveAs.h"
#include "CommandDrawArc.h"
#include "CommandDrawLine.h"
#include "CommandDrawBezier.h"
#include "CommandZoomValueChange.h"

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

void App::startCommandDrawArc()
{
   setCurrentCmd(new CommandDrawArc());
}

void App::startCommandDrawLine()
{
   setCurrentCmd(new CommandDrawLine());
}

void App::startCommandDrawBezier()
{
   setCurrentCmd(new CommandDrawBezier());
}

///////////////////////////////////////////////////////////////////////////////

void App::actionMousePressInDrawArea(int x,int y)
{
   CommandDraw* draw= dynamic_cast<CommandDraw*>(currentCommand);
   if (draw) 
      draw->posMousePress(x,y,data,userInterface);
}

void App::actionMouseMoveInDrawArea(int x,int y)
{
   CommandDraw* draw= dynamic_cast<CommandDraw*>(currentCommand);
   if (draw)
      draw->posMouseMove(x,y,data,userInterface);
}

void App::actionMouseReleaseInDrawArea(int x,int y)
{
   CommandDraw* draw= dynamic_cast<CommandDraw*>(currentCommand);
   if (draw)
      draw->posMouseRelease(x,y,data,userInterface);
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
   CommandZoomValueChange(value).exec(data,userInterface);
}