#pragma once
#ifndef INCLUDED_COMMAND_OPEN_FILE_H
#define INCLUDED_COMMAND_OPEN_FILE_H

#include "CommandIOFile.h"

class File;
class Shape;
class DataViewController;

class CommandOpenFile : public CommandIOFile
{
private:
   void drawOpenFile(UserInterface& ui,File& openedFile);
   void drawShape(UserInterface& ui,Shape& shape,DataViewController& dataViewController);
public:
   ~CommandOpenFile() {}
   CommandOpenFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_OPEN_H