#pragma once
#ifndef INCLUDED_COMMAND_CREATE_BEZIER_H
#define INCLUDED_COMMAND_CREATE_BEZIER_H

#include "Point.h"
#include "CommandCreateDraw.h"

class CommandCreateBezier : public CommandCreateDraw
{
private:
   Point initial;
   Point control;
   Point final;

   Shape& saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateBezier() {}
   CommandCreateBezier();

   void exec(Data& data,UserInterface& ui);

   void posMousePress(Point& point,Data& data,UserInterface& ui);
   void posMouseMove(Point& point,Data& data,UserInterface& ui);
   void posMouseRelease(Point& point,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_CREATE_BEZIER_H