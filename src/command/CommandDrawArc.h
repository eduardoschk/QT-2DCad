#pragma once
#ifndef INCLUDED_COMMAND_SET_SHAPE_ARC_H
#define INCLUDED_COMMAND_SET_SHAPE_ARC_H

#include "CommandDraw.h"

class CommandDrawArc : public CommandDraw
{
private:
   int id;
   Point* center;
   Point* initial;
   Point* final;

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandDrawArc() {}
   CommandDrawArc() : center(nullptr),initial(nullptr),final(nullptr) {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_SET_SHAPE_ARC_H