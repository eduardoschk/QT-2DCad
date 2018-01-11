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
   if ((windowSize - frameBorder) > viewSize)
      viewPortSize= viewSize;
   else 
      viewPortSize= windowSize - frameBorder;
}

void DataViewController::setWindowSize(Size newSize)
{
   windowSize= newSize;
   if (windowSize > viewPortSize) 
      viewPortSize= (viewSize > windowSize - frameBorder) ? windowSize - frameBorder : viewSize;
   else 
      viewPortSize= windowSize - frameBorder;
   rectPresentation= Rect(0,0,viewPortSize.getWidth(),viewPortSize.getHeight());
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
