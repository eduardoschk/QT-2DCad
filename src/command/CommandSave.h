#pragma once
#ifndef INCLUDED_COMMAND_SAVE_H
#define INCLUDED_COMMAND_SAVE_H

#include "Command.h"
class CommandSave :
    public Command
{
public:
    CommandSave() {}
    ~CommandSave() {}

    void exec( Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_SAVE_H