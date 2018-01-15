#pragma once
#ifndef INCLUDED_COMMAND_MOVE_SCROLL_H
#define INCLUDED_COMMAND_MOVE_SCROLL_H

#include "Command.h"

enum SCROL_ORIENTATION { HORIZONTAL, VERTICAL };

class CommandMoveScroll : public Command
{
private:
   int value;
   SCROL_ORIENTATION orientation;
public:
   CommandMoveScroll(int value, SCROL_ORIENTATION orientation);
   ~CommandMoveScroll() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_MOVE_SCROLL_H