#include "CommandCreateDraw.h"
#include "Shape.h"
#include "UserInterface.h"
#include "DataViewController.h"

void CommandCreateDraw::draw(UserInterface& ui,DataViewController& viewController,Shape& shape)
{
   ui.disableMouseTracking();
   ui.eraseShape(shape.getId());
   ui.drawPoints(shape.getId(),shape.getPointsToDrawInRect(viewController.getZoomScale(),viewController.getRectPresentation()));
}