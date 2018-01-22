#include "CommandCreateBezier.h"
#include "Data.h"
#include "File.h"
#include "Point.h"
#include "LineShape.h"
#include "BezierShape.h"
#include "UserInterface.h"

CommandCreateBezier::CommandCreateBezier() : initial(Point()),control(Point()),final(Point()) 
{}

///////////////////////////////////////////////////////////////////////////////

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

void CommandCreateBezier::posMousePress(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (initial.isNull())
      initial= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
   else
      control= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
   ui.activateMouseTracking();
}

void CommandCreateBezier::posMouseMove(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!final.isNull())
      if (!control.isNull()) {
         control= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
         draw(ui,dataViewController,BezierShape(id,initial,control,final));
      }
      else {
         final= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
         draw(ui,dataViewController,LineShape(id,initial,final));
      }
   else {
      final=dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
      draw(ui,dataViewController,LineShape(id,initial,final));
   }
}

void CommandCreateBezier::posMouseRelease(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   if (!control.isNull()) {
      control= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));

      Shape& bezier= saveShapeOnFile(data);
      draw(ui,dataViewController,bezier);
   }
   else {
      final= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
      draw(ui,dataViewController,LineShape(id,initial,final));
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
