#pragma once
#ifndef INCLUDED_COMMAND_CREATE_ARC_H
#define INCLUDED_COMMAND_CREATE_ARC_H

#include "Coordinate.h"
#include "CommandCreateDraw.h"

class CommandCreateArc : public CommandCreateDraw
{
private:
   Coordinate center;
   Coordinate initial;
   Coordinate final;

   Shape& saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateArc() {}
   CommandCreateArc();

   void exec(Data& data,UserInterface& ui);

   void posMousePress(Coordinate& coordinate,Data& data,UserInterface& ui);
   void posMouseMove(Coordinate& coordinate,Data& data,UserInterface& ui);
   void posMouseRelease(Coordinate& coordinate,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_CREATE_ARC_H