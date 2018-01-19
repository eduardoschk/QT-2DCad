#include "CommandCreateBezier.h"
#include "Data.h"
#include "File.h"
#include "LineShape.h"
#include "UserInterface.h"

void CommandCreateBezier::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markBezierOptionAsSelected();
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateBezier::posMousePress(Point point,Data& data,UserInterface& ui)
{
   if (initial.isNull())
      initial= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
   else
      control= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
   ui.activateMouseTracking();
}

void CommandCreateBezier::posMouseMove(Point point,Data& data,UserInterface& ui)
{
   if (!final.isNull())
      if (!control.isNull()) {
         control= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
         draw(ui,data.getCurrentFile().getDataViewController(),BezierShape(id,initial,control,final));
      }
      else {
         final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
         draw(ui,data.getCurrentFile().getDataViewController(),LineShape(id,initial,final));
      }
   else {
      final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
      draw(ui,data.getCurrentFile().getDataViewController(),LineShape(id,initial,final));
   }
}

void CommandCreateBezier::posMouseRelease(Point point,Data& data,UserInterface& ui)
{
   if (!control.isNull()) {
      control= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);

      Shape& bezier= saveShapeOnFile(data);
      draw(ui,data.getCurrentFile().getDataViewController(),bezier);
   }
   else {
      final= data.getCurrentFile().getDataViewController().fixPointViewInWorld(point);
      draw(ui,data.getCurrentFile().getDataViewController(),LineShape(id,initial,final));
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateBezier::prepareToNewDraw(Data& data)
{
   initial= control= final= Point();
   id= data.getCurrentFile().generateIdShape();
}

Shape& CommandCreateBezier::saveShapeOnFile(Data& data)
{
   BezierShape* bezier= new BezierShape(id,initial,control,final);
   data.getCurrentFile().addShapeOnFile(bezier);
   prepareToNewDraw(data);
   return *bezier;
}
