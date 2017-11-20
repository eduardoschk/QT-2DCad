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

App::App(int argc, char **argv) : QApplication(argc, argv)
{
   data= new Data();
   userInterface= new UserInterface(this);
   currentCommand= nullptr;
}

App::~App() 
{
   delete data;
   delete userInterface;
   cleanCurrentCmd();
}

///////////////////////////////////////////////////////////////////////////////

void App::run()
{
   exec();
   actionQuit();
}

///////////////////////////////////////////////////////////////////////////////

void App::cleanCurrentCmd()
{
   if ( currentCommand )
      delete currentCommand;
   currentCommand= nullptr;
}

bool App::executeCmd()
{
   if ( currentCommand )
   {
      currentCommand->exec( *data , *userInterface );
      return true;
   }
   return false;
}

///////////////////////////////////////////////////////////////////////////////

void App::actionDrawLine( int x1 , int y1 , int x2 , int y2 )
{
    cleanCurrentCmd();
    currentCommand= new CommandDrawLine( x1 , y1 , x2 , y2 );
    executeCmd();
}

void App::actionDrawBezier( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 )
{
    cleanCurrentCmd();
    currentCommand= new CommandDrawBezier( x1 , y1 , x2 , y2 , x3 , y3 );
    executeCmd();
}

void App::actionDrawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 )
{
    cleanCurrentCmd();
    currentCommand= new CommandDrawArc( x1 , y1 , x2 , y2 , x3 , y3 );
    executeCmd();
}

void App::actionCreateArhive( std::string name , int width , int height )
{
   cleanCurrentCmd();
   currentCommand= new CommandCreateFile( name , width , height);
   executeCmd();
}

void App::actionNewFile()
{
   cleanCurrentCmd();
   currentCommand= new CommandNew();
   executeCmd();
}

void App::actionOpenFile()
{
   cleanCurrentCmd();
   currentCommand= new CommandOpen();
   executeCmd();
}

void App::actionSaveFile()
{
   cleanCurrentCmd();
   currentCommand= new CommandSave();
   executeCmd();
}

void App::actionSaveAsFile()
{
   cleanCurrentCmd();
   currentCommand= new CommandSaveAs();
   executeCmd();
}

void App::actionQuit()
{
   quit();
}