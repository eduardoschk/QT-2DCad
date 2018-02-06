#pragma once
#include "Command.h"

class DataViewController;

class CommandChangeDrawArea : public Command
{
private:
   void configVerticalScroll(DataViewController& dataView,UserInterface& ui);
   void configHorizontalScroll(DataViewController& dataView,UserInterface& ui);
protected:
   void repaint(Data& data,UserInterface& ui);
   void verifyTheNeedForScrollInDrawArea(DataViewController& dataView,UserInterface& ui);
public:
   ~CommandChangeDrawArea() {}
   CommandChangeDrawArea() {}

   virtual void exec(Data& data,UserInterface& ui) = 0;
};

