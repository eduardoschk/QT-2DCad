#pragma once
#ifndef INCLUDED_COMMAND_CREATE_LINE_H
#define INCLUDED_COMMAND_CREATE_LINE_H

#include "CommandCreateDraw.h"
#include "Point.h"

class LineShape;

class CommandCreateLine : public CommandCreateDraw
{
private:
   int id;
   Point initial;
   Point final;

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);
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