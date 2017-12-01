#pragma once
#ifndef INCLUDED_COMMAND_SET_SHAPE_ARC_H
#define INCLUDED_COMMAND_SET_SHAPE_ARC_H

#include "CommandDraw.h"

class CommandDrawArc : public CommandDraw
{
public:
   ~CommandDrawArc() {}
   CommandDrawArc() {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);

};

#endif // INCLUDED_COMMAND_SET_SHAPE_ARC_H