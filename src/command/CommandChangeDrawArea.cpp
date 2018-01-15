#include "CommandChangeDrawArea.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandChangeDrawArea::repaint(Data& data,UserInterface& ui)
{
   ui.clearArea();
   for (std::pair<int,std::deque<Point>> points : data.getCurrentFile().repaintRect(data.getCurrentFile().getDataViewController().getRectPresentation()))
      ui.drawPoints(points.first,points.second);
}

void CommandChangeDrawArea::resizeDrawArea(DataViewController& data,UserInterface& ui)
{
   ui.setSizeViewPort(data.getViewPortSize());
   ui.setSizeDrawArea(data.getSizeDrawArea());
}

void CommandChangeDrawArea::verifyTheNeedForScrollInDrawArea(DataViewController& dataView,UserInterface& ui)
{
   if (dataView.verifyNeedVerticalScroll()) {
      int limit= dataView.calcVerticalScrollLimit();
      int pageStep= dataView.calcVerticalScrollPageStep();

      ui.createVerticalScrollBar(pageStep,limit);
      ui.setVerticalScrollBarPosition(dataView.getRectPresentation().initialY);
   } else 
      ui.destructVerticalScrollBar();

   if (dataView.verifyNeedHorizontalScroll()) {
      int limit= dataView.calcHorizontalScrollLimit();
      int pageStep= dataView.calcHorizontalScrollPageStep();

      ui.createHorizontalScrollBar(pageStep,limit);
      ui.setHorizontalScrollBarPosition(dataView.getRectPresentation().initialX);
   }
   else
      ui.destructHorizontalScrollBar();
}