#pragma once
#ifndef INCLUDED_COMMAND_RESIZE_WINDOW_H
#define INCLUDED_COMMAND_RESIZE_WINDOW_H

#include "CommandChangeDrawArea.h"

class Size;

class CommandResizeWindow : public CommandChangeDrawArea
{
private:
   Size& size;
public:
   ~CommandResizeWindow() {}
   CommandResizeWindow(Size& size);

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_RESIZE_WINDOW_H