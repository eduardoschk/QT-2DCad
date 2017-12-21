#include "CommandCreateArc.h"
#include "Data.h"
#include "File.h"
#include "ArcShape.h"
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

void CommandCreateArc::posMousePress(int x,int y,Data&,UserInterface& ui)
{
   if (center.isNull())
      center= Point(x,y);
   else
      initial= Point(x,y);
   ui.activateMouseTracking();
}

void CommandCreateArc::posMouseMove(int x,int y,Data&,UserInterface& ui)
{
   if (!initial.isNull()) {
      final= Point(x,y);
      draw(ui);
   }
}

void CommandCreateArc::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   if (!final.isNull()) {
      final= Point(x,y);
      draw(ui);
      saveShapeOnFile(data);
   }  
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateArc::prepareToNewDraw(Data& data)
{
   center= initial= final= Point();
   id= data.getCurrentFile().generateIdShape();
}

void CommandCreateArc::draw(UserInterface& ui)
{
   ui.eraseDraw(id);
   ui.disableMouseTracking();
   ui.drawArc(id,center.x,center.y,initial.x,initial.y,final.x,final.y);
}

void CommandCreateArc::saveShapeOnFile(Data& data)
{
   data.getCurrentFile().addShapeOnFile(new ArcShape(id,center,initial,final));
   prepareToNewDraw(data);
}