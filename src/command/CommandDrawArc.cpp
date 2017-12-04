#include "CommandDrawArc.h"
#include "Data.h"
#include "File.h"
#include "ArcShape.h"
#include "UserInterface.h"

void CommandDrawArc::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile())
      id= data.getCurrentFile().generateIdShape();
   ui.setShapeArc();
}

///////////////////////////////////////////////////////////////////////////////

void CommandDrawArc::posMousePress(int x,int y,Data&,UserInterface&)
{
   if (!center)
      center= new Point(x,y);
   else
      initial= new Point(x,y);
}

void CommandDrawArc::posMouseMove(int x,int y,Data&,UserInterface& ui)
{
   if (final)
      delete final;
   final= new Point(x,y);
   draw(ui);
}

void CommandDrawArc::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   if (final) {
      delete final;
      final= new Point(x,y);
      draw(ui);
      saveShapeOnFile(data);
   }  
}

///////////////////////////////////////////////////////////////////////////////

void CommandDrawArc::prepareToNewDraw(Data& data)
{
   center= initial= final= nullptr;
   id= data.getCurrentFile().generateIdShape();
}

void CommandDrawArc::draw(UserInterface& ui)
{
   ui.eraseDraw(id);
   ui.drawArc(id,center->x,center->y,initial->x,initial->y,final->x,final->y);
}

void CommandDrawArc::saveShapeOnFile(Data& data)
{
   data.getCurrentFile().addShapeOnFile(new ArcShape(id,center,initial,final));
   prepareToNewDraw(data);
}