#pragma once
#ifndef INCLUDED_COMMAND_DRAW_BEZIER_H
#define INCLUDED_COMMAND_DRAW_BEZIER_H

#include "Command.h"

class Point;

class CommandDrawBezier :
    public Command
{
private:
   Point * final;
    Point * initial;
    Point * control;
public:
    CommandDrawBezier( int xInit , int yInit , int xControl , int yControl , int xFinal , int yFinal );
    ~CommandDrawBezier() {}

    void exec( Data & data , UserInterface & ui );
};

#endif // INCLUDED_COMMAND_DRAW_BEZIER_H