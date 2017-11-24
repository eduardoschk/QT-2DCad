#pragma once
#ifndef INCLUDED_COMMAND_OPEN_H
#define INCLUDED_COMMAND_OPEN_H

#include "CommandIO.h"

class Shape;

class CommandOpen : public CommandIO
{
private:
   void drawShape(UserInterface& ui,Shape& shape);
public:
   CommandOpen() {}
   ~CommandOpen() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_OPEN_H