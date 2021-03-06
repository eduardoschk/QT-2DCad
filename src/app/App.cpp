#include "App.h"
#include "Data.h"
#include "UserInterface.h"
#include "Command.h"
#include "CommandOpenFile.h"
#include "CommandSaveFile.h"
#include "CommandSaveAsFile.h"
#include "CommandCreateArc.h"
#include "CommandCreateLine.h"
#include "CommandMoveScroll.h"
#include "CommandCreateBezier.h"
#include "CommandResizeWindow.h"
#include "CommandCreateNewFile.h"
#include "CommandZoomValueChange.h"

App::~App()
{
   closeAllWindows();
   setCurrentCmd(nullptr);
}

App::App(int argc,char **argv) : QApplication(argc,argv),data(),userInterface(*this)
{
   currentCommand= nullptr;
}

///////////////////////////////////////////////////////////////////////////////

void App::run()
{
   userInterface.init();
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

void App::startMoveXScroll(int value)
{
   CommandMoveScroll(value,SCROL_ORIENTATION::HORIZONTAL).exec(data,userInterface);
}

void App::startMoveYScroll(int value)
{
   CommandMoveScroll(value,SCROL_ORIENTATION::VERTICAL).exec(data,userInterface);
}

///////////////////////////////////////////////////////////////////////////////

void App::startCommandResizeWindow(Size& size)
{
   CommandResizeWindow(size).exec(data,userInterface);
}

void App::startCommandZoomValueChange(int value)
{
   CommandZoomValueChange(value).exec(data,userInterface);
}

///////////////////////////////////////////////////////////////////////////////

void App::actionMousePressInDrawArea(Coordinate& coordinate)
{
   CommandCreateDraw* isDrawCommand= dynamic_cast<CommandCreateDraw*>(currentCommand);
   if (isDrawCommand)
      isDrawCommand->posMousePress(coordinate,data,userInterface);
}

void App::actionMouseMoveInDrawArea(Coordinate& coordinate)
{
   CommandCreateDraw* isDrawCommand= dynamic_cast<CommandCreateDraw*>(currentCommand);
   if (isDrawCommand)
      isDrawCommand->posMouseMove(coordinate,data,userInterface);
}

void App::actionMouseReleaseInDrawArea(Coordinate& coordinate)
{
   CommandCreateDraw* isDrawCommand= dynamic_cast<CommandCreateDraw*>(currentCommand);
   if (isDrawCommand)
      isDrawCommand->posMouseRelease(coordinate,data,userInterface);
}
