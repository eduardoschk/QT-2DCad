#pragma once
#ifndef INCLUDED_COMMAND_SAVE_H
#define INCLUDED_COMMAND_SAVE_H

#include "CommandIO.h"

class CommandSave : public CommandIO
{
public:
   ~CommandSave() {}
   CommandSave() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SAVE_H