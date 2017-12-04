#include "CommandZoomValueChange.h"
#include "Data.h"
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

      ui.setDrawingScale(scale);
   }
}