#pragma once
#ifndef INCLUDED_COMMAND_SAVE_AS_H
#define INCLUDED_COMMAND_SAVE_AS_H

#include "Command.h"
class CommandSaveAs :
    public Command
{
public:
    CommandSaveAs() {}
    ~CommandSaveAs() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_SAVE_AS_H
