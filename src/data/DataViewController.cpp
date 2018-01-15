#include "DataViewController.h"

DataViewController::DataViewController(Size _shapeSize)
{
   zoomScale= 1;
   viewSize= _shapeSize;
   shapeSize= viewSize;
}

///////////////////////////////////////////////////////////////////////////////

#include <iostream>

Point DataViewController::fixPointInView(Point point)
{
   point.x+= rectPresentation.initialX;
   point.y+= rectPresentation.initialY;

   if (!point.on(rectPresentation)) {
      std::cout << "Fora da apresentação" << std::endl;
      if (!point.on(viewSize.sizeRect)) {
         std::cout << "Fora de tudo" << std::endl;
      }
   }
   return point / zoomScale;
}

///////////////////////////////////////////////////////////////////////////////

float DataViewController::getZoomScale()
{
   return zoomScale;
}

void DataViewController::setScale(float scale)
{
   zoomScale= scale;
   viewSize= shapeSize * zoomScale;
   if ((windowSize - frameBorder) > viewSize) {
      viewPortSize= drawAreaSize= viewSize;
   } else {
      viewPortSize= windowSize - Size(0,footerHeight);
      drawAreaSize= windowSize - frameBorder;
   }
   rectPresentation= Rect(0,0,viewPortSize.getWidth(),viewPortSize.getHeight());
}

void DataViewController::setWindowSize(Size newSize)
{
   windowSize= newSize;
   if (windowSize > viewPortSize) {
      if (viewSize > windowSize - frameBorder) {
         viewPortSize= windowSize - Size(0,footerHeight);
         drawAreaSize= windowSize - frameBorder;
      } else {
         viewPortSize= drawAreaSize= viewSize;
      }
   } else {
      viewPortSize= windowSize - Size(0,footerHeight);
      drawAreaSize= windowSize - frameBorder;
   }
   rectPresentation= Rect(rectPresentation.initialX,rectPresentation.initialY,viewPortSize.getWidth(),viewPortSize.getHeight());
}

///////////////////////////////////////////////////////////////////////////////

Size DataViewController::getViewSize()
{
   return viewSize;
}

Size DataViewController::getShapeSize()
{
   return shapeSize;
}

Size DataViewController::getWindowSize()
{
   return windowSize;
}

Size DataViewController::getViewPortSize()
{
   return viewPortSize;
}

Size DataViewController::getSizeDrawArea()
{
   return drawAreaSize;
}

Rect DataViewController::getRectPresentation()
{
   return rectPresentation;
}

///////////////////////////////////////////////////////////////////////////////

bool DataViewController::verifyNeedVerticalScroll()
{
   return viewSize.height > viewPortSize.height;
}

bool DataViewController::verifyNeedHorizontalScroll()
{
   return viewSize.width > viewPortSize.width;
}

int DataViewController::calcVerticalScrollLimit()
{
   return viewSize.height - viewPortSize.height;
}

int DataViewController::calcVerticalScrollPageStep()
{
   return viewPortSize.height;
}

int DataViewController::calcHorizontalScrollLimit()
{
   return viewSize.width - viewPortSize.width;
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