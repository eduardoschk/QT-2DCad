#pragma once
#ifndef INCLUDED_COMMAND_CREATE_NEW_FILE_H
#define INCLUDED_COMMAND_CREATE_NEW_FILE_H

#include "CommandChangeDrawArea.h"

class CommandCreateNewFile : public CommandChangeDrawArea
{
public:
   ~CommandCreateNewFile() {}
   CommandCreateNewFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_CREATE_NEW_FILE_H