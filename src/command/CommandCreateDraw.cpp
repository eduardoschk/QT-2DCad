#include "CommandCreateDraw.h"
#include "Shape.h"
#include "UserInterface.h"
#include "DataViewController.h"

void CommandCreateDraw::draw(UserInterface& ui,DataViewController& viewController,Shape& shape)
{
   ui.disableMouseTracking();
   ui.eraseShape(shape.getId());
   ui.drawCoordinates(shape.getId(),shape.getCoordinatesToDrawInRect(viewController));
}