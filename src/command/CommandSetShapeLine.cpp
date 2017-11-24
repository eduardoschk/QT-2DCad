#include "CommandSetShapeLine.h"
#include "Data.h"
#include "ShapeTypes.h"

void CommandSetShapeLine::exec(Data& data,UserInterface&)
{
   data.resetPoints();
   data.setShapeType(SHAPE_TYPE::LINE);
}
