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

   void posMousePress(int x,int y,Data& data,UserInterface& ui);
   void posMouseMove(int x,int y,Data& data,UserInterface& ui);
   void posMouseRelease(int x,int y,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_CREATE_ARC_H