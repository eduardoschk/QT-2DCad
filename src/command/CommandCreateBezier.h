#pragma once
#ifndef INCLUDED_COMMAND_CREATE_BEZIER_H
#define INCLUDED_COMMAND_CREATE_BEZIER_H

#include "CommandCreateDraw.h"

class CommandCreateBezier : public CommandCreateDraw
{
private:
   int id;
   Point initial;
   Point control;
   Point final;

   void draw(UserInterface& ui);
   void saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateBezier() {}
   CommandCreateBezier() {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_CREATE_BEZIER_H