#include "CommandCreateBezier.h"
#include "Data.h"
#include "File.h"
#include "BezierShape.h"
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

void CommandCreateBezier::posMousePress(int x,int y,Data&,UserInterface& ui)
{
   if (initial.isNull())
      initial= Point(x,y);
   else
      control= Point(x,y);
   ui.activateMouseTracking();
}

void CommandCreateBezier::posMouseMove(int x,int y,Data&,UserInterface& ui)
{
   if (!final.isNull())
      if (!control.isNull()) 
         control= Point(x,y);
      else 
         final= Point(x,y);
   else
      final= Point(x,y);
   draw(ui);
}

void CommandCreateBezier::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
   if (!control.isNull()) {
      control= Point(x,y);

      draw(ui);
      saveShapeOnFile(data);
   }
   else {
      final= Point(x,y);
      draw(ui);
   }
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateBezier::prepareToNewDraw(Data& data)
{
   initial= control= final= Point();
   id= data.getCurrentFile().generateIdShape();
}

void CommandCreateBezier::draw(UserInterface& ui)
{
   ui.eraseDraw(id);
   ui.disableMouseTracking();
   if (!control.isNull())
      ui.drawBezier(id,initial.x,initial.y,control.x,control.y,final.x,final.y);
   else
      ui.drawLine(id,initial.x,initial.y,final.x,final.y);
}

void CommandCreateBezier::saveShapeOnFile(Data& data)
{
   data.getCurrentFile().addShapeOnFile(new BezierShape(id,initial,control,final));
   prepareToNewDraw(data);
}