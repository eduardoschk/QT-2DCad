#include "CommandChangeDrawArea.h"
#include "Data.h"
#include "File.h"
#include "Rect.h"
#include "UserInterface.h"

void CommandChangeDrawArea::configVerticalScroll(DataViewController& dataView,UserInterface& ui)
{
   int limit= dataView.calcVerticalScrollLimit();
   int pageStep= dataView.calcVerticalScrollPageStep();

   ui.createVerticalScrollBar(pageStep,limit);
   ui.setVerticalScrollBarPosition(dataView.getRectPresentation().initialY);
}

void CommandChangeDrawArea::configHorizontalScroll(DataViewController& dataView,UserInterface& ui)
{
   int limit= dataView.calcHorizontalScrollLimit();
   int pageStep= dataView.calcHorizontalScrollPageStep();

   ui.createHorizontalScrollBar(pageStep,limit);
   ui.setHorizontalScrollBarPosition(dataView.getRectPresentation().initialX);
}

///////////////////////////////////////////////////////////////////////////////

void CommandChangeDrawArea::repaint(Data& data,UserInterface& ui)
{
   for (std::pair<int,std::deque<Coordinate>> coordinates : data.getCurrentFile().repaintRectInPresentation()) {
      if (coordinates.second.size() > 0)
         ui.drawCoordinates(coordinates.first,coordinates.second);
      else
         ui.eraseShape(coordinates.first);
   }
}

void CommandChangeDrawArea::verifyTheNeedForScrollInDrawArea(DataViewController& dataView,UserInterface& ui)
{
   if (dataView.verifyNeedVerticalScroll())
      configVerticalScroll(dataView,ui);
   else 
      ui.destructVerticalScrollBar();

   if (dataView.verifyNeedHorizontalScroll())
      configHorizontalScroll(dataView,ui);
   else
      ui.destructHorizontalScrollBar();
}
