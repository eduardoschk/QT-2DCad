#include "CommandMousePressInDrawArea.h"
#include "Data.h"

void CommandMousePressInDrawArea::exec(Data& data,UserInterface&)
{
   switch (data.getSelectShapeType()) {
      case SHAPE_TYPE::LINE:     drawingLine(data);      break;
      case SHAPE_TYPE::ARC:      drawingArc(data);       break;
      case SHAPE_TYPE::BEZIER:   drawingBezier(data);    break;
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandMousePressInDrawArea::drawingArc(Data& data)
{
   data.addPoint(point);
}

void CommandMousePressInDrawArea::drawingLine(Data& data)
{
   data.addPoint(point);
}

void CommandMousePressInDrawArea::drawingBezier(Data& data)
{
   data.addPoint(point);
}