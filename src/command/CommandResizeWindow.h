#pragma once
#ifndef INCLUDED_COMMAND_RESIZE_WINDOW_H
#define INCLUDED_COMMAND_RESIZE_WINDOW_H

#include "Command.h"
#include "Size.h"

class CommandResizeWindow : public Command
{
private:
   int height,width;
public:
   ~CommandResizeWindow() {}
   CommandResizeWindow(int _height, int _width);

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_RESIZE_WINDOW_H