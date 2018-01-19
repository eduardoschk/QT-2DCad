#pragma once
#ifndef INCLUDED_DATA_VIEW_CONTROLLER_H
#define INCLUDED_DATA_VIEW_CONTROLLER_H

#include <deque>
#include "Size.h"
#include "Rect.h"

class Point;

class DataViewController
{
private:
   const int footerHeight= 105;
   const int scrollSizeWidget= 15;
   const Size frameBorder= Size(scrollSizeWidget,footerHeight+scrollSizeWidget);
   const Size defaultDraw= Size(100,100);

   float zoomScale;

   Size windowSize;
   Size viewPortSize;
   Size currentShapesSize;
   Size originalShapesSize;
   Rect rectPresentation;

public:
   ~DataViewController() {}
   DataViewController();

   void newShape(Rect rect);

   float getScale();
   void setScale(float scale);
   void setWindowSize(Size newSize);

   void setXPresentation(int value);
   void setYPresentation(int value);
   
   Point fixPoint(Point point);
   Point fixPointWorldInView(Point point);
   Point fixPointViewInWorld(Point point);

   Size getWindowSize();
   Rect getRectPresentation();
   
   bool verifyDiffScale();

   bool verifyNeedVerticalScroll();
   bool verifyNeedHorizontalScroll();

   int calcVerticalScrollLimit();
   int calcHorizontalScrollLimit();
   int calcVerticalScrollPageStep();
   int calcHorizontalScrollPageStep();
};

#endif // INCLUDED_DATA_VIEW_CONTROLLER_H