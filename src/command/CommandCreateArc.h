#pragma once
#ifndef INCLUDED_COMMAND_CREATE_ARC_H
#define INCLUDED_COMMAND_CREATE_ARC_H

#include "Point.h"
#include "ArcShape.h"
#include "CommandCreateDraw.h"

class CommandCreateArc : public CommandCreateDraw
{
private:
   Point center;
   Point initial;
   Point final;

   Shape& saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateArc() {}
   CommandCreateArc() {}

   void exec(Data& data,UserInterface& ui);

   void posMousePress(Point point,Data& data,UserInterface& ui);
   void posMouseMove(Point point,Data& data,UserInterface& ui);
   void posMouseRelease(Point point,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_CREATE_ARC_H