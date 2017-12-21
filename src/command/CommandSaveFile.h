#pragma once
#ifndef INCLUDED_COMMAND_SAVE_FILE_H
#define INCLUDED_COMMAND_SAVE_FILE_H

#include "CommandIOFile.h"

class CommandSaveFile : public CommandIOFile
{
public:
   ~CommandSaveFile() {}
   CommandSaveFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SAVE_FILE_H