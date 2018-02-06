#include "CommandCreateLine.h"
#include "Data.h"
#include "File.h"
#include "LineShape.h"
#include "UserInterface.h"

void CommandCreateLine::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markLineOptionAsSelected();
      ui.setTipMessage("Select the position to start the line and move the mouse down to the end");
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::posMousePress(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   initial= dataViewController.repairCoordinateViewToWorld(coordinate);
   ui.activateMouseTracking();
}

void CommandCreateLine::posMouseMove(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   final= dataViewController.repairCoordinateViewToWorld(coordinate);
   draw(ui,dataViewController,LineShape(id,initial,final));
}

void CommandCreateLine::posMouseRelease(Coordinate& coordinate,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   final= dataViewController.repairCoordinateViewToWorld(coordinate);

   Shape& line= saveShapeOnFile(data);
   draw(ui,dataViewController,line);
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::prepareToNewDraw(Data& data)
{
   id= data.getCurrentFile().generateIdShape();
}

Shape& CommandCreateLine::saveShapeOnFile(Data& data)
{
   LineShape* line= new LineShape(id,initial,final);
   data.getCurrentFile().addShapeOnFile(line);
   prepareToNewDraw(data);
   return *line;
}
