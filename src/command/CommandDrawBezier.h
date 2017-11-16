#pragma once
#ifndef INCLUDED_COMMAND_DRAW_BEZIER_H
#define INCLUDED_COMMAND_DRAW_BEZIER_H

#include "Command.h"

class Point;

class CommandDrawBezier :
    public Command
{
private:
    Point * initial;
    Point * control;
    Point * final;
public:
    CommandDrawBezier( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );
    ~CommandDrawBezier() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_DRAW_BEZIER_H