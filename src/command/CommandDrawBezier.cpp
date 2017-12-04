#include "CommandDrawBezier.h"
#include "Data.h"
#include "File.h"
#include "BezierShape.h"
#include "UserInterface.h"

void CommandDrawBezier::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile())
      id= data.getCurrentFile().generateIdShape();
   ui.setShapeBezier();
}

///////////////////////////////////////////////////////////////////////////////

void CommandDrawBezier::posMousePress(int x,int y,Data&,UserInterface&)
{
   if (!initial)
      initial= new Point(x,y);
   else
      control= new Point(x,y);
}

void CommandDrawBezier::posMouseMove(int x,int y,Data&,UserInterface& ui)
{
   if (final)
      if (control) {
         delete control;
         control= new Point(x,y);
      } 
      else {
         delete final;
         final= new Point(x,y);
      }
   else
      final= new Point(x,y);
   draw(ui);
}

void CommandDrawBezier::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   if (control) {
      delete control;
      control= new Point(x,y);

      draw(ui);
      saveShapeOnFile(data);
   }
   else {
      delete final;
      final= new Point(x,y);
      draw(ui);
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandDrawBezier::prepareToNewDraw(Data& data)
{
   initial= control= final= nullptr;
   id= data.getCurrentFile().generateIdShape();
}

void CommandDrawBezier::draw(UserInterface& ui)
{
   ui.eraseDraw(id);
   if (control)
      ui.drawBezier(id,initial->x,initial->y,control->x,control->y,final->x,final->y);
   else
      ui.drawLine(id,initial->x,initial->y,final->x,final->y);
}

void CommandDrawBezier::saveShapeOnFile(Data& data)
{
   data.getCurrentFile().addShapeOnFile(new BezierShape(id,initial,control,final));
   prepareToNewDraw(data);
}