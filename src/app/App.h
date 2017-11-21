#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <QApplication>
#include <string>

#include "UserInterface.h"
#include "Data.h"

class Command;

enum MENU_OPTIONS {
    DRAW_LINE,
    DRAW_ARC,
    DRAW_BEZIER,
    NEW_FILE ,
    OPEN_FILE ,
    SAVE_FILE ,
    SAVE_AS_FILE ,
    EXIT
};

class App : public QApplication
{
private:
    Data data;
    Command* currentCommand;
    UserInterface userInterface;

    void setCurrentCmd(Command* newCm);

public:
    ~App();
    App(int argc, char **argv);

    void run();

    void actionDrawLine( int x1 , int y1 , int x2 , int y2 );
    void actionDrawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );
    void actionDrawBezier( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );

    void actionQuit();
    void actionNewFile();
    void actionOpenFile();
    void actionSaveFile();
    void actionSaveAsFile();
    void actionCreateFile( std::string name , int width , int height );
};

#endif // INCLUDED_APP_H