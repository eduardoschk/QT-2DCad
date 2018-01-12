#pragma once
#ifndef INCLUDED_COMMAND_CREATE_LINE_H
#define INCLUDED_COMMAND_CREATE_LINE_H

#include "Point.h"
#include "LineShape.h"
#include "CommandCreateDraw.h"

class CommandCreateLine : public CommandCreateDraw
{
private:
   Point initial;
   Point final;

   Shape& saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateLine() {}
   CommandCreateLine() {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(Point point,Data& data,UserInterface& ui);
   void posMouseMove(Point point,Data& data,UserInterface& ui);
   void posMouseRelease(Point point,Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SET_SHAPE_LINE_H