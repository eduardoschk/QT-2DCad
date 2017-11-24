#pragma once
#ifndef INCLUDED_COMMAND_MOUSE_PRESS_IN_DRAW_AREA_H
#define INCLUDED_COMMAND_MOUSE_PRESS_IN_DRAW_AREA_H

#include "Command.h"
#include "Point.h"

class CommandMousePressInDrawArea : public Command
{
private:
   Point point;

   void drawingArc(Data& data);
   void drawingLine(Data& data);
   void drawingBezier(Data& data);

public:
   CommandMousePressInDrawArea(Point& _point) { point= _point; }
   ~CommandMousePressInDrawArea() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_MOUSE_PRESS_IN_DRAW_AREA_H