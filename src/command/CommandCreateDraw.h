#pragma once
#ifndef INCLUDED_COMMAND_CREATE_DRAW_H
#define INCLUDED_COMMAND_CREATE_DRAW_H

#include <deque>
#include "Command.h"
#include "Point.h"

class Shape;
class DataViewController;

class CommandCreateDraw : public Command
{
protected:
   int id;

   virtual Shape& saveShapeOnFile(Data& data) = 0;
   virtual void prepareToNewDraw(Data& data) = 0;
   void draw(UserInterface& ui,DataViewController& viewController,Shape& shape);

public:
   virtual ~CommandCreateDraw() {}
   CommandCreateDraw() {}

   virtual void posMousePress(Point& point,Data& data,UserInterface& ui) = 0;
   virtual void posMouseMove(Point& point,Data& data,UserInterface& ui) = 0;
   virtual void posMouseRelease(Point& point,Data& data,UserInterface& ui) = 0;

};

#endif // INCLUDED_COMMAND_DRAW_H