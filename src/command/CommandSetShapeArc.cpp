#include "CommandSetShapeArc.h"
#include "Data.h"
#include "ShapeTypes.h"

void CommandSetShapeArc::exec(Data& data,UserInterface&)
{
   data.resetPoints();
   data.setShapeType(SHAPE_TYPE::ARC);
}