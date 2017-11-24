#pragma once
#ifndef INCLUDED_COMMAND_MOUSE_RELEASE_IN_DRAW_AREA_H
#define INCLUDED_COMMAND_MOUSE_RELEASE_IN_DRAW_AREA_H

#include "Command.h"
#include "Point.h"

class CommandMouseReleaseInDrawArea : public Command
{
private:
   Point point;

   void drawingArc(Data& data,UserInterface& ui);
   void drawingLine(Data& data,UserInterface& ui);
   void drawingBezier(Data& data,UserInterface& ui);

public:
   CommandMouseReleaseInDrawArea(Point& _point) { point= _point; }
   ~CommandMouseReleaseInDrawArea() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_MOUSE_RELEASE_IN_DRAW_AREA_H