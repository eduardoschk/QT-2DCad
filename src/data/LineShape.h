#pragma once
#ifndef INCLUDED_LINE_SHAPE_H
#define INCLUDED_LINE_SHAPE_H

#include "Shape.h"

class LineShape : public Shape
{
private:
   Point originalInitialPoint;
   Point originalFinalPoint;

   Point currentInitialPoint;
   Point currentFinalPoint;

   Rect calcRectShape(float scale);
   std::deque<Point> calcPointsToDraw(float scale);
public:
   ~LineShape() {}
   LineShape(int _id,Point& _initial,Point& _final);

   int getType();

   Rect getOriginalRectShape();
   Rect getCurrentRectShape(DataViewController& dataViewController);

   std::deque<Point> getSelectedPoints();
   std::deque<Point> getPointsToDraw(DataViewController& dataViewController);
   std::deque<Point> getPointsToDrawInRect(DataViewController& dataViewController);
};

#endif // INCLUDED_LINE_SHAPE_H