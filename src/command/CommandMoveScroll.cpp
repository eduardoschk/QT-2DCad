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
   switch (orientation) {
      case VERTICAL:
         data.getCurrentFile().getDataViewController().setYPresentation(value);
      break;
      case HORIZONTAL:
         data.getCurrentFile().getDataViewController().setXPresentation(value);
      break;
   }
   data.getCurrentFile().repaintRect(data.getCurrentFile().getDataViewController().getRectPresentation());
   ui.clearArea();
   for (std::pair<int,std::deque<Point>> points : data.getCurrentFile().repaintRect(data.getCurrentFile().getDataViewController().getRectPresentation()))
      ui.drawPoints(points.first,points.second); 
}