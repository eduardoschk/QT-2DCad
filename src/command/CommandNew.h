#pragma once
#ifndef INCLUDED_COMMAND_NEW_H
#define INCLUDED_COMMAND_NEW_H

#include "Command.h"

class CommandNew : public Command
{
public:
   ~CommandNew() {}
   CommandNew() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_NEW_H