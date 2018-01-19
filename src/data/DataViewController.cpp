#include "DataViewController.h"
#include "Rect.h"
#include "Point.h"

#include <memory>

DataViewController::DataViewController()
{
   zoomScale= 1;
   originalShapesSize= defaultDraw;
}

///////////////////////////////////////////////////////////////////////////////

void DataViewController::newShape(Rect rect)
{
   if (!originalShapesSize.contains(rect)) {
      originalShapesSize= (originalShapesSize << rect) + defaultDraw;
      currentShapesSize= originalShapesSize * zoomScale;
   }
}

///////////////////////////////////////////////////////////////////////////////

Point DataViewController::fixPointWorldInView(Point point)
{
   if (verifyDiffScale()) {
      point.x= (point.x * currentShapesSize.width) / originalShapesSize.width;
      point.y= (point.y * currentShapesSize.height) / originalShapesSize.height;
   }
   return point;
}

Point DataViewController::fixPoint(Point point)
{
   point.x-= rectPresentation.initialX;
   point.y-= rectPresentation.initialY;
   return point;
}

Point DataViewController::fixPointViewInWorld(Point point)
{
   point.x+= rectPresentation.initialX;
   point.y+= rectPresentation.initialY;

   if (verifyDiffScale()) {
      point.x= point.x * (originalShapesSize.width) / currentShapesSize.width;
      point.y= point.y * (originalShapesSize.height) / currentShapesSize.height;
   }
   return point;
}

///////////////////////////////////////////////////////////////////////////////

float DataViewController::getScale()
{
   return zoomScale;
}

void DataViewController::setScale(float scale)
{
   zoomScale= scale;
   currentShapesSize= originalShapesSize * zoomScale;

   if (currentShapesSize > windowSize)
      viewPortSize= windowSize - frameBorder;
   else 
      viewPortSize= windowSize;

   rectPresentation= Rect(0,0,viewPortSize.getWidth(),viewPortSize.getHeight());
}

void DataViewController::setWindowSize(Size newSize)
{
   windowSize= newSize;

   if (currentShapesSize > windowSize)
      viewPortSize= windowSize - frameBorder;
   else
      viewPortSize= windowSize;

   rectPresentation= Rect(rectPresentation.initialX,rectPresentation.initialY,viewPortSize.getWidth(),viewPortSize.getHeight());
}

///////////////////////////////////////////////////////////////////////////////

Size DataViewController::getWindowSize()
{
   return windowSize;
}

Rect DataViewController::getRectPresentation()
{
   std::shared_ptr<Rect> rect(new Rect(rectPresentation.initialX - 100,rectPresentation.initialY - 100,rectPresentation.width + 100,rectPresentation.height + 100));
   return *rect.get();
}

///////////////////////////////////////////////////////////////////////////////

bool DataViewController::verifyDiffScale()
{
   return zoomScale != 1;
}

bool DataViewController::verifyNeedVerticalScroll()
{
   return currentShapesSize.height > viewPortSize.height;
}

bool DataViewController::verifyNeedHorizontalScroll()
{
   return currentShapesSize.width > viewPortSize.width;
}

///////////////////////////////////////////////////////////////////////////////

int DataViewController::calcVerticalScrollLimit()
{
   return currentShapesSize.height - viewPortSize.height;
}

int DataViewController::calcHorizontalScrollLimit()
{
   return currentShapesSize.width - viewPortSize.width;
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