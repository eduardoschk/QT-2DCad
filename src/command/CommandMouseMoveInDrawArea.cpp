#include <deque>
#include "CommandMouseMoveInDrawArea.h"
#include "Data.h"
#include "UserInterface.h"

void CommandMouseMoveInDrawArea::exec(Data& data,UserInterface& ui)
{
   switch (data.getSelectShapeType()) {
      case SHAPE_TYPE::LINE:     drawingLine(data,ui);      break;
      case SHAPE_TYPE::ARC:      drawingArc(data,ui);       break;
      case SHAPE_TYPE::BEZIER:   drawingBezier(data,ui);    break;
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandMouseMoveInDrawArea::drawingArc(Data& data,UserInterface& ui)
{
   ui.drawTempArc(data.getPoints()[0].x,data.getPoints()[0].y,data.getPoints()[1].x,data.getPoints()[1].y,point.x,point.y);
}

void CommandMouseMoveInDrawArea::drawingLine(Data& data,UserInterface& ui)
{
   ui.drawTempLine(data.getPoints()[0].x,data.getPoints()[0].y,point.x,point.y);
}

void CommandMouseMoveInDrawArea::drawingBezier(Data& data,UserInterface& ui)
{
   if (data.getPoints().size() > 1) {
      ui.drawTempBezier(data.getPoints()[0].x,data.getPoints()[0].y,point.x,point.y,data.getPoints()[1].x,data.getPoints()[1].y);
   }
   else {
      ui.drawTempLine(data.getPoints()[0].x,data.getPoints()[0].y,point.x,point.y);
   }
}