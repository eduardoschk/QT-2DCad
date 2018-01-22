#include "CommandCreateArc.h"
#include "Data.h"
#include "File.h"
#include "Point.h"
#include "ArcShape.h"
#include "UserInterface.h"

CommandCreateArc::CommandCreateArc() : initial(Point()),center(Point()),final(Point())
{}

///////////////////////////////////////////////////////////////////////////////

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

void CommandCreateArc::posMousePress(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (center.isNull())
      center= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
   else
      initial= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
   ui.activateMouseTracking();
}

void CommandCreateArc::posMouseMove(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!initial.isNull()) {
      final= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
      draw(ui,dataViewController,ArcShape(id,center,initial,final));
   }
}

void CommandCreateArc::posMouseRelease(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!final.isNull()) {
      final= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
      Shape& arc= saveShapeOnFile(data);
      draw(ui,dataViewController,arc);
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
