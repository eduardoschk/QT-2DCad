#pragma once
#ifndef INCLUDED_COMMAND_CHANGE_SHAPE_H
#define INCLUDED_COMMAND_CHANGE_SHAPE_H

#include "Command.h"
class CommandChangeShape :
    public Command
{
public:
    CommandChangeShape() {}
    ~CommandChangeShape() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_CHANGE_SHAPE_H