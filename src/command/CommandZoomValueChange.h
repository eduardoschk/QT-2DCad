#pragma once
#ifndef INCLUDED_COMMAND_ZOOM_VALUE_CHANGE_H
#define INCLUDED_COMMAND_ZOOM_VALUE_CHANGE_H

#include "CommandChangeDrawArea.h"

class CommandZoomValueChange : public CommandChangeDrawArea
{
private:
   int zoom;
   float getScaleByZoomValue();
public:
   ~CommandZoomValueChange() {}
   CommandZoomValueChange(int value) { zoom= value; }

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_ZOOM_VALUE_CHANGE_H