#pragma once
#ifndef INCLUDED_SET_SHAPE_BEZIER_H
#define INCLUDED_SET_SHAPE_BEZIER_H

#include "CommandDraw.h"

class CommandDrawBezier : public CommandDraw
{
private:
   int id;
   Point* initial;
   Point* control;
   Point* final;

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandDrawBezier() {}
   CommandDrawBezier() : initial(nullptr),control(nullptr),final(nullptr) {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

};

#endif // INCLUDED_SET_SHAPE_BEZIER_H