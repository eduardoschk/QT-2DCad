#pragma once
#ifndef INCLUDED_COMMAND_CREATE_DRAW_H
#define INCLUDED_COMMAND_CREATE_DRAW_H

#include <deque>
#include "Command.h"

class Shape;
class DataViewController;

class CommandCreateDraw : public Command
{
protected:
   int id;

   virtual Shape& saveShapeOnFile(Data& data) = 0;
   virtual void prepareToNewDraw(Data& data) = 0;
   virtual void draw(UserInterface& ui,DataViewController& viewController,Shape& shape);

public:
   virtual ~CommandCreateDraw() {}
   CommandCreateDraw() {}

   virtual void posMousePress(int x,int y,Data& data,UserInterface& ui) = 0;
   virtual void posMouseMove(int x,int y,Data& data,UserInterface& ui) = 0;
   virtual void posMouseRelease(int x,int y,Data& data,UserInterface& ui) = 0;

};

#endif // INCLUDED_COMMAND_DRAW_H