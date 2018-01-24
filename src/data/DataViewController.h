#pragma once
#ifndef INCLUDED_DATA_VIEW_CONTROLLER_H
#define INCLUDED_DATA_VIEW_CONTROLLER_H

#include <deque>
#include "Size.h"
#include "Rect.h"
#include "CoordinateMapper.h"

class Coordinate;

class DataViewController
{
private:
   float zoomScale;

   Size windowSize;
   Size viewPortSize;
   Rect rectPresentation;

   CoordinateMapper coordinateMapper;

   void recalcSizes();
   void recalcViewPortSize();

public:
   ~DataViewController() {}
   DataViewController();

   void newShape(Rect& rect);

   float getScale();
   void setScale(float scale);
   void setWindowSize(Size& newSize);

   void setXPresentation(int value);
   void setYPresentation(int value);
   
   Coordinate discardScroll(Coordinate& coordinate);

   Coordinate repairCoordinateWorldToView(Coordinate& coordinate);
   Coordinate repairCoordinateViewToWorld(Coordinate& coordinate);

   Size& getWindowSize();
   Rect& getRectPresentation();
   
   bool rectIsInPresentation(Rect& rect);

   bool verifyNeedVerticalScroll();
   bool verifyNeedHorizontalScroll();

   int calcVerticalScrollLimit();
   int calcHorizontalScrollLimit();
   int calcVerticalScrollPageStep();
   int calcHorizontalScrollPageStep();
};

#endif // INCLUDED_DATA_VIEW_CONTROLLER_H