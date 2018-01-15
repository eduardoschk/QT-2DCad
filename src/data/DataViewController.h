#pragma once
#ifndef INCLUDED_DATA_VIEW_CONTROLLER_H
#define INCLUDED_DATA_VIEW_CONTROLLER_H

#include "Size.h"
#include "Point.h"

class DataViewController
{
private:
   const int footerHeight= 105;
   const int scrollSizeWidget= 15;
   const Size frameBorder= Size(scrollSizeWidget,footerHeight+scrollSizeWidget);

   float zoomScale;

   Size viewSize;
   Size shapeSize;
   Size windowSize;
   Size viewPortSize;
   Size drawAreaSize;
   Rect rectPresentation;

public:
   ~DataViewController() {}
   DataViewController(Size _sizeShape);

   float getZoomScale();
   void setScale(float scale);
   void setWindowSize(Size newSize);

   void setXPresentation(int value);
   void setYPresentation(int value);
   Point fixPointInView(Point point);

   Size getViewSize();
   Size getShapeSize();
   Size getWindowSize();
   Size getViewPortSize();
   Size getSizeDrawArea();
   Rect getRectPresentation();
   
   bool verifyNeedVerticalScroll();
   bool verifyNeedHorizontalScroll();

   int calcVerticalScrollLimit();
   int calcHorizontalScrollLimit();
   int calcVerticalScrollPageStep();
   int calcHorizontalScrollPageStep();
};

#endif // INCLUDED_DATA_VIEW_CONTROLLER_H