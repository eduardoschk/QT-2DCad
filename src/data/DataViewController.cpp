#include "DataViewController.h"
#include "Rect.h"
#include "Size.h"
#include "Coordinate.h"

const int footerHeight= 105;
const int scrollSizeWidget= 15;
Size& defaultDraw= Size(100,100);

DataViewController::DataViewController() : coordinateMapper(defaultDraw,defaultDraw)
{
   zoomScale= 1;
   rectPresentation= Rect(0,0,defaultDraw.width,defaultDraw.height);
}

///////////////////////////////////////////////////////////////////////////////

void DataViewController::newShape(Rect& rect)
{
   if (!coordinateMapper.getWorldSize().contains(rect)) {
      coordinateMapper.setWorldSize((coordinateMapper.getWorldSize() << rect) + defaultDraw);
      coordinateMapper.setDeviceSize(coordinateMapper.getWorldSize() * zoomScale);
   }
}

///////////////////////////////////////////////////////////////////////////////

Coordinate DataViewController::discardScroll(Coordinate& coordinate)
{
   Coordinate fixedCoordenate;

   fixedCoordenate.x= coordinate.x - rectPresentation.initialX;
   fixedCoordenate.y= coordinate.y - rectPresentation.initialY;

   return fixedCoordenate;
}

Coordinate DataViewController::repairCoordinateWorldToView(Coordinate& coordinate)
{
   return coordinateMapper.mapCoordinateWorldToDevice(coordinate);
}

Coordinate DataViewController::repairCoordinateViewToWorld(Coordinate& coordinate)
{
   Coordinate fixedCoordenate;

   fixedCoordenate.x= coordinate.x + rectPresentation.initialX;
   fixedCoordenate.y= coordinate.y + rectPresentation.initialY;

   return coordinateMapper.mapCoordinateDeviceToWorld(fixedCoordenate);
}

///////////////////////////////////////////////////////////////////////////////

float DataViewController::getScale()
{
   return zoomScale;
}

void DataViewController::recalcSizes()
{
   if (coordinateMapper.getDeviceSize() > windowSize)
      recalcViewPortSize();
   else
      viewPortSize= windowSize;
}

void DataViewController::recalcViewPortSize()
{
   viewPortSize= windowSize - Size(0,footerHeight);
   if (verifyNeedVerticalScroll())
      viewPortSize= viewPortSize - Size(scrollSizeWidget,0);
   if (verifyNeedHorizontalScroll())
      viewPortSize= viewPortSize - Size(0,scrollSizeWidget);
}

///////////////////////////////////////////////////////////////////////////////

void DataViewController::setScale(float scale)
{
   zoomScale= scale;
   Coordinate centerCoordenate(rectPresentation.initialX + (rectPresentation.width / 2),rectPresentation.initialY + (rectPresentation.height / 2));
   Coordinate originalCenterCoordinate= coordinateMapper.mapCoordinateDeviceToWorld(centerCoordenate);

   coordinateMapper.setDeviceSize(coordinateMapper.getWorldSize() * zoomScale);

   Coordinate newCenterCoordinate= coordinateMapper.mapCoordinateWorldToDevice(originalCenterCoordinate);

   recalcSizes();

   int newInitialX,newInitialY;
   newInitialX= newInitialY= 0;

   if (verifyNeedHorizontalScroll())
      newInitialX= newCenterCoordinate.x - (viewPortSize.getWidth() / 2);
   if (verifyNeedVerticalScroll())
      newInitialY= newCenterCoordinate.y - (viewPortSize.getHeight() / 2);

   rectPresentation= Rect(newInitialX,newInitialY,viewPortSize.getWidth(),viewPortSize.getHeight());
}

void DataViewController::setWindowSize(Size& newSize)
{
   windowSize= newSize;
   recalcSizes();

   rectPresentation= Rect(rectPresentation.getInitialCordinate(),viewPortSize.getWidth(),viewPortSize.getHeight());
}

///////////////////////////////////////////////////////////////////////////////

Size& DataViewController::getWindowSize()
{
   return windowSize;
}

Rect& DataViewController::getRectPresentation()
{
   return rectPresentation;
}

bool DataViewController::rectIsInPresentation(Rect& rect)
{
   bool shapeOnRect;
   if (rect > rectPresentation)
      shapeOnRect= rect.fullyContained(rectPresentation);
   else 
      shapeOnRect= rectPresentation.fullyContained(rect);
   
   shapeOnRect= shapeOnRect || rectPresentation.partiallycontained(rect);

   return shapeOnRect;
}

///////////////////////////////////////////////////////////////////////////////

bool DataViewController::verifyNeedVerticalScroll()
{
   return coordinateMapper.getDeviceSize().height > viewPortSize.height;
}

bool DataViewController::verifyNeedHorizontalScroll()
{
   return coordinateMapper.getDeviceSize().width > viewPortSize.width;
}

///////////////////////////////////////////////////////////////////////////////

int DataViewController::calcVerticalScrollLimit()
{
   return coordinateMapper.getDeviceSize().height - viewPortSize.height;
}

int DataViewController::calcHorizontalScrollLimit()
{
   return coordinateMapper.getDeviceSize().width - viewPortSize.width;
}

int DataViewController::calcVerticalScrollPageStep()
{
   return viewPortSize.height;
}

int DataViewController::calcHorizontalScrollPageStep()
{
   return viewPortSize.width;
}

///////////////////////////////////////////////////////////////////////////////

void DataViewController::setXPresentation(int value)
{
   rectPresentation.initialX= value;
}

void DataViewController::setYPresentation(int value)
{
   rectPresentation.initialY= value;
}