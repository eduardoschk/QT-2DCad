#pragma once
#ifndef INCLUDED_COMMAND_CREATE_BEZIER_H
#define INCLUDED_COMMAND_CREATE_BEZIER_H

#include "Coordinate.h"
#include "CommandCreateDraw.h"

class CommandCreateBezier : public CommandCreateDraw
{
private:
   Coordinate initial;
   Coordinate control;
   Coordinate final;

   Shape& saveShapeOnFile(Data& data);
   void prepareToNewDraw(Data& data);

public:
   ~CommandCreateBezier() {}
   CommandCreateBezier();

   void exec(Data& data,UserInterface& ui);

   void posMousePress(Coordinate& coordinate,Data& data,UserInterface& ui);
   void posMouseMove(Coordinate& coordinate,Data& data,UserInterface& ui);
   void posMouseRelease(Coordinate& coordinate,Data& data,UserInterface& ui);

};

#endif // INCLUDED_COMMAND_CREATE_BEZIER_H