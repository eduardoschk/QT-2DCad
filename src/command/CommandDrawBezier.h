#pragma once
#ifndef INCLUDED_SET_SHAPE_BEZIER_H
#define INCLUDED_SET_SHAPE_BEZIER_H

#include "CommandDraw.h"

class CommandDrawBezier : public CommandDraw
{
public:
   ~CommandDrawBezier() {}
   CommandDrawBezier() {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);
};

#endif // INCLUDED_SET_SHAPE_BEZIER_H