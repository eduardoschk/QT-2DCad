#pragma once
#ifndef INCLUDED_COMMAND_SAVE_AS_H
#define INCLUDED_COMMAND_SAVE_AS_H

#include "CommandIO.h"

class CommandSaveAs : public CommandIO
{
public:
    CommandSaveAs() {}
    ~CommandSaveAs() {}

    void exec(Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_SAVE_AS_H
