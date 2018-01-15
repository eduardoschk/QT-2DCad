#pragma once
#include "Command.h"

class DataViewController;

class CommandChangeDrawArea : public Command
{
protected:
   void repaint(Data& data,UserInterface& ui);
   void resizeDrawArea(DataViewController& data,UserInterface& ui);
   void verifyTheNeedForScrollInDrawArea(DataViewController& data,UserInterface& ui);
public:
   ~CommandChangeDrawArea() {}
   CommandChangeDrawArea() {}

   virtual void exec(Data& data,UserInterface& ui) = 0;
};

