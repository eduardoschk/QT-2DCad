#include "App.h"
#include "UserInterface.h"
#include "Data.h"
#include "Command.h"
#include "CommandNew.h"
#include "CommandOpen.h"
#include "CommandSave.h"
#include "CommandDrawLine.h"
#include "CommandDrawArc.h"
#include "CommandSaveAs.h"
#include "CommandCreateFile.h"
#include "CommandDrawBezier.h"

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

void App::actionDrawLine(int x1,int y1,int x2,int y2)
{
   setCurrentCmd(new CommandDrawLine(x1,y1,x2,y2));
}

void App::actionDrawBezier(int x1,int y1,int x2,int y2,int x3,int y3)
{
   setCurrentCmd(new CommandDrawBezier(x1,y1,x2,y2,x3,y3));
}

void App::actionDrawArc(int x1,int y1,int x2,int y2,int x3,int y3)
{
   setCurrentCmd(new CommandDrawArc(x1,y1,x2,y2,x3,y3));
}

void App::actionCreateFile(std::string name,int width,int height)
{
   setCurrentCmd(new CommandCreateFile(name,width,height));
}

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