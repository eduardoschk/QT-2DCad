#include "App.h"
#include "Data.h"
#include "UserInterface.h"
#include "Command.h"
#include "CommandCreateNewFile.h"
#include "CommandOpenFile.h"
#include "CommandSaveFile.h"
#include "CommandSaveAsFile.h"
#include "CommandCreateArc.h"
#include "CommandCreateLine.h"
#include "CommandCreateBezier.h"
#include "CommandZoomValueChange.h"

App::~App()
{
   closeAllWindows();
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
   setCurrentCmd(new CommandCreateArc());
}

void App::startCommandDrawLine()
{
   setCurrentCmd(new CommandCreateLine());
}

void App::startCommandDrawBezier()
{
   setCurrentCmd(new CommandCreateBezier());
}

///////////////////////////////////////////////////////////////////////////////

void App::actionMousePressInDrawArea(int x,int y)
{
   CommandCreateDraw* isDrawCommand= dynamic_cast<CommandCreateDraw*>(currentCommand);
   if (isDrawCommand)
      isDrawCommand->posMousePress(x,y,data,userInterface);
}

void App::actionMouseMoveInDrawArea(int x,int y)
{
   CommandCreateDraw* isDrawCommand= dynamic_cast<CommandCreateDraw*>(currentCommand);
   if (isDrawCommand)
      isDrawCommand->posMouseMove(x,y,data,userInterface);
}

void App::actionMouseReleaseInDrawArea(int x,int y)
{
   CommandCreateDraw* isDrawCommand= dynamic_cast<CommandCreateDraw*>(currentCommand);
   if (isDrawCommand)
      isDrawCommand->posMouseRelease(x,y,data,userInterface);
}

///////////////////////////////////////////////////////////////////////////////

void App::startCommandNewFile()
{
   setCurrentCmd(new CommandCreateNewFile());
}

void App::startCommandOpenFile()
{
   setCurrentCmd(new CommandOpenFile());
}

void App::startCommandSaveFile()
{
   setCurrentCmd(new CommandSaveFile());
}

void App::startCommandSaveAsFile()
{
   setCurrentCmd(new CommandSaveAsFile());
}

void App::startCommandQuit()
{
   quit();
}

void App::startCommandZoomValueChange(int value)
{
   CommandZoomValueChange(value).exec(data,userInterface);
}