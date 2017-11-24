#pragma once
#ifndef INCLUDED_SET_SHAPE_BEZIER_H
#define INCLUDED_SET_SHAPE_BEZIER_H

#include "Command.h"

class CommandSetShapeBezier : public Command
{
public:
   ~CommandSetShapeBezier() {}
   CommandSetShapeBezier() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_SET_SHAPE_BEZIER_H