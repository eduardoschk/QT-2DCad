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
    CommandDrawArc( int xCenter , int yCenter , int xInit , int yInit , int xFinal , int yFinal );
    ~CommandDrawArc() {}

    void exec( Data & data , UserInterface & ui );
};

#endif // INCLUDED_COMMAND_DRAW_ARC_H