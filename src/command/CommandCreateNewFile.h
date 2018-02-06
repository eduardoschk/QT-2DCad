#pragma once
#ifndef INCLUDED_COMMAND_CREATE_NEW_FILE_H
#define INCLUDED_COMMAND_CREATE_NEW_FILE_H

#include "CommandChangeDrawArea.h"

class File;

class CommandCreateNewFile : public CommandChangeDrawArea
{
private:
   File* file;

   bool checkIfCanCreateFile(Data& data,UserInterface& ui);
   void configDrawArea(DataViewController& viewController,UserInterface& ui);
public:
   ~CommandCreateNewFile() {}
   CommandCreateNewFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_CREATE_NEW_FILE_H