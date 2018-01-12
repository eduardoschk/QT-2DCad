#pragma once
#ifndef INCLUDED_COMMAND_MOVE_SCROLL_H
#define INCLUDED_COMMAND_MOVE_SCROLL_H

#include "Command.h"

class CommandMoveScroll :
   public Command
{
public:
   CommandMoveScroll();
   ~CommandMoveScroll();
};

#endif // INCLUDED_COMMAND_MOVE_SCROLL_H