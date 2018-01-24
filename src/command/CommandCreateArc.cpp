#include "CommandCreateArc.h"
#include "Data.h"
#include "File.h"
#include "Coordinate.h"
#include "ArcShape.h"
#include "UserInterface.h"

CommandCreateArc::CommandCreateArc() : initial(Coordinate()),center(Coordinate()),final(Coordinate()) {}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateArc::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markArcOptionAsSelected();
      ui.setTipMessage("Select the center point of the circle, after, select the initial point to draw and this point will be your radius default, with the mouse down move to draw your arc");
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateArc::posMousePress(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (center.isNull())
      center= dataViewController.repairCoordinateViewToWorld(coordinate);
   else
      initial= dataViewController.repairCoordinateViewToWorld(coordinate);
   ui.activateMouseTracking();
}

void CommandCreateArc::posMouseMove(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!initial.isNull()) {
      final= dataViewController.repairCoordinateViewToWorld(coordinate);
      draw(ui,dataViewController,ArcShape(id,center,initial,final));
   }
}

void CommandCreateArc::posMouseRelease(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!final.isNull()) {
      final= dataViewController.repairCoordinateViewToWorld(coordinate);
      Shape& arc= saveShapeOnFile(data);
      draw(ui,dataViewController,arc);
   }  
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateArc::prepareToNewDraw(Data& data)
{
   center= initial= final= Coordinate();
   id= data.getCurrentFile().generateIdShape();
}

Shape& CommandCreateArc::saveShapeOnFile(Data& data)
{
   ArcShape* arc= new ArcShape(id,center,initial,final);
   data.getCurrentFile().addShapeOnFile(arc);
   prepareToNewDraw(data);
   return *arc;
}
