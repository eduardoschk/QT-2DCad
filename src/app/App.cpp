#include "App.h"
#include "UserInterface.h"
#include "Data.h"
#include "Command.h"
#include "CommandNew.h"

App::App(int argc, char **argv) : QApplication(argc, argv)
{
    data= new Data();
    userInterface= new UserInterface(this);
    currentCommand= nullptr;
}

App::~App() {}

void App::run()
{
    exec();
}

bool App::executeCmd()
{
    return true;
}

void App::cleanCurrentCmd()
{
    if ( currentCommand )
        delete currentCommand;
    currentCommand= nullptr;
}

void App::actionNewFile( std::string pathAndFileName , int width , int height )
{
    cleanCurrentCmd();
    currentCommand= new CommandNew( pathAndFileName , width, height);
    currentCommand->exec(*data, *userInterface);
}

void App::actionOpenFile( std::string pathAndFile )
{
    int a= 5;
}
