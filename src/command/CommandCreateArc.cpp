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

void CommandCreateArc::posMousePress(int x,int y,Data& data,UserInterface& ui)
{
   if (center.isNull())
      center= data.getCurrentFile().getDataViewController().fixPointInView(Point(x,y));
   else
      initial= data.getCurrentFile().getDataViewController().fixPointInView(Point(x,y));
   ui.activateMouseTracking();
}

void CommandCreateArc::posMouseMove(int x,int y,Data& data,UserInterface& ui)
{
   if (!initial.isNull()) {
      final= data.getCurrentFile().getDataViewController().fixPointInView(Point(x,y));
      draw(ui,data.getCurrentFile().getDataViewController(),ArcShape(id,center,initial,final));
   }
}

void CommandCreateArc::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   if (!final.isNull()) {
      final= data.getCurrentFile().getDataViewController().fixPointInView(Point(x,y));
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
