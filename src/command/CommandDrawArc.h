#pragma once
#ifndef INCLUDED_COMMAND_DRAW_ARC_H
#define INCLUDED_COMMAND_DRAW_ARC_H

#include "Command.h"

class Point;

class CommandDrawArc :
    public Command
{
private:
    Point * center;
    Point * initial;
    Point * final;
public:
    CommandDrawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );
    ~CommandDrawArc();

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_DRAW_ARC_H