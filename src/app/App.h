#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <QApplication>
#include <string>

class Command;
class UserInterface;
class Data;

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

class App :
    public QApplication
{
private:
    Data * data;
    UserInterface * userInterface;
    Command * currentCommand;

    bool executeCmd();
    void cleanCurrentCmd();
public:
    ~App();
    App(int argc, char **argv);

    void run();

    void actionDrawLine( int x1 , int y1 , int x2 , int y2 );
    void actionDrawBezier( int x1 , int y1 , int x2 , int y2 , int x3, int y3 );
    void actionDrawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );

    void actionNewFile( std::string pathAndFile, int width, int height);
    void actionOpenFile( std::string pathAndFile );
    void actionSaveFile();
    void actionSaveAsFile();
    void actionQuit();
};

#endif // INCLUDED_APP_H