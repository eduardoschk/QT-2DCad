#include "CommandDrawLine.h"
#include "Data.h"
#include "File.h"
#include "LineShape.h"
#include "UserInterface.h"

void CommandDrawLine::exec(Data& data,UserInterface& ui) 
{
   if (data.hasFile())
      id= data.getCurrentFile().generateIdShape();
   ui.setShapeLine();
}

///////////////////////////////////////////////////////////////////////////////

void CommandDrawLine::posMousePress(int x,int y,Data&,UserInterface&)
{
   initial= new Point(x,y);
}

void CommandDrawLine::posMouseMove(int x,int y,Data&,UserInterface& ui)
{
   if (final)
      delete final;
   final= new Point(x,y);

   draw(ui);
}

void CommandDrawLine::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   if (final)
      delete final;
   final= new Point(x,y);

   draw(ui);
   saveShapeOnFile(data);
}

///////////////////////////////////////////////////////////////////////////////

void CommandDrawLine::prepareToNewDraw(Data& data)
{
   initial= final= nullptr;
   id= data.getCurrentFile().generateIdShape();
}

void CommandDrawLine::draw(UserInterface& ui)
{ 
   ui.eraseDraw(id);
   ui.drawLine(id,initial->x,initial->y,final->x,final->y);
}

void CommandDrawLine::saveShapeOnFile(Data& data)
{
   data.getCurrentFile().addShapeOnFile(new LineShape(id,initial,final));
   prepareToNewDraw(data);
}