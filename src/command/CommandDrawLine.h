#pragma once
#ifndef INCLUDED_COMMAND_SET_SHAPE_LINE_H
#define INCLUDED_COMMAND_SET_SHAPE_LINE_H

#include "CommandDraw.h"

class LineShape;

class CommandDrawLine : public CommandDraw
{
private:
   Point* initial;
   LineShape* currentDraw;

   int a= 0;

public:
   ~CommandDrawLine() {}
   CommandDrawLine() : currentDraw(nullptr) {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);
};

#endif // INCLUDED_COMMAND_SET_SHAPE_LINE_H