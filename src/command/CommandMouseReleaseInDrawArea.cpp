#include "CommandMouseReleaseInDrawArea.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"
#include "LineShape.h"
#include "BezierShape.h"
#include "ArcShape.h"
#include "Point.h"

void CommandMouseReleaseInDrawArea::exec(Data& data,UserInterface& ui)
{
   switch (data.getSelectShapeType()) {
      case SHAPE_TYPE::LINE:     drawingLine(data,ui);      break;
      case SHAPE_TYPE::ARC:      drawingArc(data,ui);       break;
      case SHAPE_TYPE::BEZIER:   drawingBezier(data,ui);    break;
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandMouseReleaseInDrawArea::drawingArc(Data& data,UserInterface& ui)
{
   if (data.getPoints().size() > 1) {
      data.getCurrentFile().addShapeOnFile(new ArcShape(new Point(data.getPoints()[0].x,data.getPoints()[0].y),new Point(data.getPoints()[1].x,data.getPoints()[1].y),new Point(point.x,point.y)));
      ui.drawArc(data.getPoints()[0].x,data.getPoints()[0].y,data.getPoints()[1].x,data.getPoints()[1].y,point.x,point.y);
      data.resetPoints();
   }
}

void CommandMouseReleaseInDrawArea::drawingLine(Data& data,UserInterface& ui)
{
   data.getCurrentFile().addShapeOnFile(new LineShape(new Point(data.getPoints()[0].x,data.getPoints()[0].y),new Point(point.x,point.y)));
   ui.drawLine(data.getPoints()[0].x,data.getPoints()[0].y,point.x,point.y);
   data.resetPoints();
}

void CommandMouseReleaseInDrawArea::drawingBezier(Data& data,UserInterface& ui)
{
   if (data.getPoints().size() == 1) {
      data.addPoint(point);
   }
   else {
      data.getCurrentFile().addShapeOnFile(new BezierShape(new Point(data.getPoints()[0].x,data.getPoints()[0].y),new Point(point.x,point.y),new Point(data.getPoints()[1].x,data.getPoints()[1].y)));
      ui.drawBezier(data.getPoints()[0].x,data.getPoints()[0].y,point.x,point.y,data.getPoints()[1].x,data.getPoints()[1].y);
      data.resetPoints();
   }   
}