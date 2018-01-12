#include "CommandZoomValueChange.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandZoomValueChange::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      float scale;

      switch (zoom) {
         case ZOOM::ONE:   scale= 0.125;   break;
         case ZOOM::TWO:   scale= 0.25;    break;
         case ZOOM::THREE: scale= 0.5;     break;
         case ZOOM::FOUR:  scale= 1;       break;
         case ZOOM::FIVE:  scale= 2;       break;
         case ZOOM::SIX:   scale= 3;       break;
         case ZOOM::SEVEN: scale= 4;       break;
         case ZOOM::EIGHT: scale= 5;       break;
         case ZOOM::NINE:  scale= 6;       break;
         case ZOOM::TEN:   scale= 8;       break;
      }
      data.getCurrentFile().getDataViewController().setScale(scale);

      ui.clearArea();
      ui.setSizeDrawArea(data.getCurrentFile().getDataViewController().getViewPortSize());
      for (std::pair<int,std::deque<Point>> points : data.getCurrentFile().repaintAll()) 
         ui.drawPoints(points.first,points.second);
      ui.createVerticalScrollBar(data.getCurrentFile().getDataViewController().calcVerticalScrollPageStep(),data.getCurrentFile().getDataViewController().calcVerticalScrollLimit());
      ui.createHorizontalScrollBar(data.getCurrentFile().getDataViewController().calcHorizontalScrollPageStep(),data.getCurrentFile().getDataViewController().calcHorizontalScrollLimit());
   }
}