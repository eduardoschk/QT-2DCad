#pragma once
#ifndef INCLUDED_COMMAND_SAVE_AS_FILE_H
#define INCLUDED_COMMAND_SAVE_AS_FILE_H

#include "CommandIOFile.h"

class CommandSaveAsFile : public CommandIOFile
{
public:
   ~CommandSaveAsFile() {}
   CommandSaveAsFile() {}

   void exec(Data& data , UserInterface& ui );
};

#endif // INCLUDED_COMMAND_SAVE_AS_FILE_H
