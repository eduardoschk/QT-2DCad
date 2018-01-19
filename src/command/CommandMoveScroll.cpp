#include "CommandMoveScroll.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

CommandMoveScroll::CommandMoveScroll(int _value,SCROL_ORIENTATION _orientation)
{
   value= _value;
   orientation= _orientation;
}

///////////////////////////////////////////////////////////////////////////////

void CommandMoveScroll::exec(Data& data,UserInterface& ui)
{
   DataViewController& dataViewController=  data.getCurrentFile().getDataViewController();

   switch (orientation) {
      case VERTICAL:
         dataViewController.setYPresentation(value);
      break;
      case HORIZONTAL:
         dataViewController.setXPresentation(value);
      break;
   }
   repaint(data,ui);
}