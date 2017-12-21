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
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::posMousePress(int x,int y,Data&,UserInterface& ui)
{
   initial= Point(x,y);
   ui.activateMouseTracking();
}

void CommandCreateLine::posMouseMove(int x,int y,Data&,UserInterface& ui)
{
   final= Point(x,y);
   draw(ui);
}

void CommandCreateLine::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   final= Point(x,y);

   draw(ui);
   saveShapeOnFile(data);
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::prepareToNewDraw(Data& data)
{
   id= data.getCurrentFile().generateIdShape();
}

void CommandCreateLine::draw(UserInterface& ui)
{ 
   ui.eraseDraw(id);
   ui.disableMouseTracking();
   ui.drawLine(id,initial.x,initial.y,final.x,final.y);
}

void CommandCreateLine::saveShapeOnFile(Data& data)
{
   data.getCurrentFile().addShapeOnFile(new LineShape(id,initial,final));
   prepareToNewDraw(data);
}