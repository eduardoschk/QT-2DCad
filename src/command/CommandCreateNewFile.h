#pragma once
#ifndef INCLUDED_COMMAND_CREATE_NEW_FILE_H
#define INCLUDED_COMMAND_CREATE_NEW_FILE_H

#include "Command.h"

class CommandCreateNewFile : public Command
{
public:
   ~CommandCreateNewFile() {}
   CommandCreateNewFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_CREATE_NEW_FILE_H