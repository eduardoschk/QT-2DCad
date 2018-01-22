#include "DataViewController.h"
#include "Rect.h"
#include "Size.h"
#include "Point.h"

const int footerHeight= 105;
const int scrollSizeWidget= 15;
const Size& frameBorder= Size(scrollSizeWidget,footerHeight + scrollSizeWidget);
const Size& defaultDraw= Size(100,100);

DataViewController::DataViewController() : originalShapesSize(Size(defaultDraw)),windowSize(Size()),viewPortSize(Size()),currentShapesSize(Size()),rectPresentation(Rect())
{
   zoomScale= 1;
}

///////////////////////////////////////////////////////////////////////////////

void DataViewController::newShape(Rect& rect)
{
   if (!originalShapesSize.contains(rect)) {
      originalShapesSize= (originalShapesSize << rect) + defaultDraw;
      currentShapesSize= originalShapesSize * zoomScale;
   }
}

///////////////////////////////////////////////////////////////////////////////

Point DataViewController::fixScroll(Point point)
{
   point.x+= rectPresentation.initialX;
   point.y+= rectPresentation.initialY;
   return point;
}

Point DataViewController::fixPointWorldInView(Point point)
{
   if (verifyDiffScale()) {
      point.x= (point.x * currentShapesSize.width) / originalShapesSize.width;
      point.y= (point.y * currentShapesSize.height) / originalShapesSize.height;
   }
   return point;
}

Point DataViewController::discardScroll(Point point)
{
   point.x-= rectPresentation.initialX;
   point.y-= rectPresentation.initialY;
   return point;
}

Point DataViewController::fixPointViewInWorld(Point point)
{
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
   Point centerPoint= Point(rectPresentation.initialX + (rectPresentation.width / 2),rectPresentation.initialY + (rectPresentation.height / 2));
   Point originalCenterPoint= fixPointViewInWorld(centerPoint);
   
   currentShapesSize= originalShapesSize * zoomScale;

   Point newCenterPoint= fixPointWorldInView(originalCenterPoint);

   if (currentShapesSize > windowSize)
      viewPortSize= windowSize - frameBorder;
   else 
      viewPortSize= windowSize;

   int newInitialX,newInitialY;
   newInitialX= newInitialY= 0;

   if (verifyNeedHorizontalScroll()) {
      newInitialX= newCenterPoint.x - (viewPortSize.getWidth() / 2);
   }
   if (verifyNeedVerticalScroll()) {
      newInitialY= newCenterPoint.y - (viewPortSize.getHeight() / 2);
   }

   rectPresentation= Rect(newInitialX,newInitialY,viewPortSize.getWidth(),viewPortSize.getHeight());
}

void DataViewController::setWindowSize(Size& newSize)
{
   windowSize= newSize;

   if (currentShapesSize > windowSize)
      viewPortSize= windowSize - frameBorder;
   else
      viewPortSize= windowSize;

   rectPresentation= Rect(rectPresentation.initialX,rectPresentation.initialY,viewPortSize.getWidth(),viewPortSize.getHeight());
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