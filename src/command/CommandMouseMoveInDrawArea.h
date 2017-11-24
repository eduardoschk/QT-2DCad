#pragma once
#ifndef INCLUDED_COMMAND_MOUSE_MOVE_IN_DRAW_AREA_H
#define INCLUDED_COMMAND_MOUSE_MOVE_IN_DRAW_AREA_H

#include "Command.h"
#include "Point.h"

class CommandMouseMoveInDrawArea : public Command
{
private:
   Point point;

   void drawingArc(Data& data,UserInterface& ui);
   void drawingLine(Data& data,UserInterface& ui);
   void drawingBezier(Data& data,UserInterface& ui);

public:
   CommandMouseMoveInDrawArea(Point& _point) { point= _point; }
   ~CommandMouseMoveInDrawArea() {}
   
   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_MOUSE_MOVE_IN_DRAW_AREA_H