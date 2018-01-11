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

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_SET_SHAPE_LINE_H