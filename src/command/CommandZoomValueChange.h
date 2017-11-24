#pragma once
#ifndef INCLUDED_COMMAND_ZOOM_VALUE_CHANGE_H
#define INCLUDED_COMMAND_ZOOM_VALUE_CHANGE_H

#include "Command.h"
#include "ZoomControl.h"

class CommandZoomValueChange : public Command
{
private:
   int zoom;
public:
   ~CommandZoomValueChange() {}
   CommandZoomValueChange(int value) { zoom= value; }

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_ZOOM_VALUE_CHANGE_H