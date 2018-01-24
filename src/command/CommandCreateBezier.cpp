#include "CommandCreateBezier.h"
#include "Data.h"
#include "File.h"
#include "Coordinate.h"
#include "LineShape.h"
#include "BezierShape.h"
#include "UserInterface.h"

CommandCreateBezier::CommandCreateBezier() : initial(Coordinate()),control(Coordinate()),final(Coordinate()) {}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateBezier::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markBezierOptionAsSelected();
      ui.setTipMessage("Draw a line and select the start point to the create a curvature and move the mouse down to end of bezier control");
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateBezier::posMousePress(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (initial.isNull())
      initial= dataViewController.repairCoordinateViewToWorld(coordinate);
   else
      control= dataViewController.repairCoordinateViewToWorld(coordinate);
   ui.activateMouseTracking();
}

void CommandCreateBezier::posMouseMove(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!final.isNull())
      if (!control.isNull()) {
         control= dataViewController.repairCoordinateViewToWorld(coordinate);
         draw(ui,dataViewController,BezierShape(id,initial,control,final));
      }
      else {
         final= dataViewController.repairCoordinateViewToWorld(coordinate);
         draw(ui,dataViewController,LineShape(id,initial,final));
      }
   else {
      final=dataViewController.repairCoordinateViewToWorld(coordinate);
      draw(ui,dataViewController,LineShape(id,initial,final));
   }
}

void CommandCreateBezier::posMouseRelease(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!control.isNull()) {
      control= dataViewController.repairCoordinateViewToWorld(coordinate);

      Shape& bezier= saveShapeOnFile(data);
      draw(ui,dataViewController,bezier);
   }
   else {
      final= dataViewController.repairCoordinateViewToWorld(coordinate);
      draw(ui,dataViewController,LineShape(id,initial,final));
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateBezier::prepareToNewDraw(Data& data)
{
   initial= control= final= Coordinate();
   id= data.getCurrentFile().generateIdShape();
}

Shape& CommandCreateBezier::saveShapeOnFile(Data& data)
{
   BezierShape* bezier= new BezierShape(id,initial,control,final);
   data.getCurrentFile().addShapeOnFile(bezier);
   prepareToNewDraw(data);
   return *bezier;
}
