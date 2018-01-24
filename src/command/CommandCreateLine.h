#pragma once
#ifndef INCLUDED_COMMAND_CREATE_LINE_H
#define INCLUDED_COMMAND_CREATE_LINE_H

#include "Coordinate.h"
#include "CommandCreateDraw.h"

class CommandCreateLine : public CommandCreateDraw
{
private:
   Coordinate initial;
   Coordinate final;

   Shape& saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateLine() {}
   CommandCreateLine();

   void exec(Data& data,UserInterface& ui);

   void posMousePress(Coordinate& coordinate,Data& data,UserInterface& ui);
   void posMouseMove(Coordinate& coordinate,Data& data,UserInterface& ui);
   void posMouseRelease(Coordinate& coordinate,Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SET_SHAPE_LINE_H