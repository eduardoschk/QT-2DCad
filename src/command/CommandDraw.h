#pragma once
#ifndef INCLUDED_COMMAND_DRAW_H
#define INCLUDED_COMMAND_DRAW_H

#include "Point.h"
#include "Command.h"

class CommandDraw : public Command
{
public:
   CommandDraw() {}
   virtual ~CommandDraw() {}

   virtual void posMousePress(int x,int y,Data& data,UserInterface& ui) = 0;
   virtual void posMouseMove(int x,int y,Data& data,UserInterface& ui) = 0;
   virtual void posMouseRelease(int x,int y,Data& data,UserInterface& ui) = 0;

   virtual void draw(UserInterface& ui) = 0;
   virtual void saveShapeOnFile(Data& data) = 0;
};

#endif // INCLUDED_COMMAND_DRAW_H