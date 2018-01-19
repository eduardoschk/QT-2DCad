#include "CommandCreateLine.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandCreateLine::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markLineOptionAsSelected();
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::posMousePress(Point point,Data& data,UserInterface& ui)
{
   initial= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
   ui.activateMouseTracking();
}

void CommandCreateLine::posMouseMove(Point point,Data& data,UserInterface& ui)
{
   final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
   auto a= LineShape(id,initial,final);
   draw(ui,data.getCurrentFile().getDataViewController(),a);
}

void CommandCreateLine::posMouseRelease(Point point,Data& data,UserInterface& ui)
{
   final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);

   Shape& line= saveShapeOnFile(data);
   draw(ui,data.getCurrentFile().getDataViewController(),line);
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
