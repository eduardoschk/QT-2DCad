#pragma once
#ifndef INCLUDED_COMMAND_OPEN_FILE_H
#define INCLUDED_COMMAND_OPEN_FILE_H

#include "CommandIOFile.h"

class Shape;

class CommandOpenFile : public CommandIOFile
{
private:
   void drawShape(UserInterface& ui,Shape& shape);
public:
   ~CommandOpenFile() {}
   CommandOpenFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_OPEN_H