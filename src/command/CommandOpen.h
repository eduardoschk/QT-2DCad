#pragma once
#ifndef INCLUDED_COMMAND_OPEN_H
#define INCLUDED_COMMAND_OPEN_H

#include "Command.h"

class CommandOpen :
    public Command
{
public:
    CommandOpen() {}
    ~CommandOpen() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_OPEN_H