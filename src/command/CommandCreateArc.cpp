#include "CommandCreateArc.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandCreateArc::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markArcOptionAsSelected();
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateArc::posMousePress(Point point,Data& data,UserInterface& ui)
{
   if (center.isNull())
      center= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
   else
      initial= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
   ui.activateMouseTracking();
}

void CommandCreateArc::posMouseMove(Point point,Data& data,UserInterface& ui)
{
   if (!initial.isNull()) {
      final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
      draw(ui,data.getCurrentFile().getDataViewController(),ArcShape(id,center,initial,final));
   }
}

void CommandCreateArc::posMouseRelease(Point point,Data& data,UserInterface& ui)
{
   if (!final.isNull()) {
      final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
      Shape& arc= saveShapeOnFile(data);
      draw(ui,data.getCurrentFile().getDataViewController(),arc);
   }  
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateArc::prepareToNewDraw(Data& data)
{
   center= initial= final= Point();
   id= data.getCurrentFile().generateIdShape();
}

Shape& CommandCreateArc::saveShapeOnFile(Data& data)
{
   ArcShape* arc= new ArcShape(id,center,initial,final);
   data.getCurrentFile().addShapeOnFile(arc);
   prepareToNewDraw(data);
   return *arc;
}
