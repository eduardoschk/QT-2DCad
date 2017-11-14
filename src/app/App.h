#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <QApplication>
#include <string>

class Command;
class UserInterface;
class Data;

enum MENU_OPTIONS {
    CHANGED_SHAPE ,
    NEW_FILE ,
    OPEN_FILE ,
    SAVE_FILE ,
    SAVE_AS_FILE ,
    EXIT
};

class App :
    public QApplication
{
private:
    Data * data;
    UserInterface * userInterface;
    Command * currentCommand;

    bool executeCmd();
    void cleanCurrentCmd();
    bool createCmd( int menuOption );
public:
    ~App();
    App(int argc, char **argv);

    void run();

    void actionNewFile( std::string pathAndFile, int width, int height);
    void actionOpenFile( std::string pathAndFile );
};

#endif // INCLUDED_APP_H