#pragma once
#ifndef INCLUDED_COMMAND_SET_SHAPE_ARC_H
#define INCLUDED_COMMAND_SET_SHAPE_ARC_H

#include "Command.h"

class CommandSetShapeArc : public Command
{
public:
   ~CommandSetShapeArc() {}
   CommandSetShapeArc() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SET_SHAPE_ARC_H