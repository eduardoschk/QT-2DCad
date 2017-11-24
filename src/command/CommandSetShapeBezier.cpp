#include "CommandSetShapeBezier.h"
#include "Data.h"
#include "ShapeTypes.h"

void CommandSetShapeBezier::exec(Data& data,UserInterface&)
{
   data.resetPoints();
   data.setShapeType(SHAPE_TYPE::BEZIER);
}