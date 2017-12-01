#include "CommandDrawLine.h"
#include "Data.h"
#include "File.h"
#include "LineShape.h"
#include "ShapeTypes.h"
#include "UserInterface.h"

void CommandDrawLine::exec(Data& _data,UserInterface& _ui) 
{
}

void CommandDrawLine::posMousePress(int x,int y,Data& data,UserInterface& ui)
{
   initial= new Point(x,y);
}

void CommandDrawLine::posMouseMove(int x,int y,Data& data,UserInterface& ui)
{
   ui.eraseDraw(a);
   ui.drawLine(++a,initial->x,initial->y,x,y);
}

void CommandDrawLine::posMouseRelease(int x,int y,Data& data,UserInterface& ui)
{
}

void CommandDrawLine::draw(UserInterface& ui)
{ 
}

void CommandDrawLine::saveShapeOnFile(Data& data)
{
}