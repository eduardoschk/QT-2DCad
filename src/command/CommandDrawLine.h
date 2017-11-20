#pragma once
#ifndef INCLUDED_COMMAND_DRAW_LINE_H
#define INCLUDED_COMMAND_DRAW_LINE_H

#include "Command.h"

class Point;

class CommandDrawLine :
    public Command
{
private:
    Point * initial;
    Point * final;
public:
    CommandDrawLine( int xInit , int yInit , int xFinal , int yFinal );
    ~CommandDrawLine() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_DRAW_LINE_H