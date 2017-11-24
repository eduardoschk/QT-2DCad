#pragma once
#ifndef INCLUDED_COMMAND_SET_SHAPE_LINE_H
#define INCLUDED_COMMAND_SET_SHAPE_LINE_H

#include "Command.h"

class CommandSetShapeLine : public Command
{
public:
   CommandSetShapeLine() {}
   ~CommandSetShapeLine() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SET_SHAPE_LINE_H