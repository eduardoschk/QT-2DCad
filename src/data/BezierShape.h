#pragma once
#ifndef INCLUDED_BEZIER_SHAPE_H
#define INCLUDED_BEZIER_SHAPE_H

#include "Shape.h"

class BezierShape : public Shape
{
private:
   Point originalInitialPoint;
   Point originalControlPoint;
   Point originalFinalPoint;

   Point currentInitialPoint;
   Point currentControlPoint;
   Point currentFinalPoint;

   Rect calcRectShape(float scale);
   std::deque<Point> calcPointsToDraw(float scale);

   float calcX(float distance);
   float calcY(float distance);
   Point calcPoint(float distance);

public:
   ~BezierShape() {}
   BezierShape(int _id,Point& _initial,Point& _control,Point& _final);

   int getType();

   Rect getOriginalRectShape();
   Rect getCurrentRectShape(DataViewController& dataViewController);

   std::deque<Point> getSelectedPoints();
   std::deque<Point> getPointsToDraw(DataViewController& dataViewController);
   std::deque<Point> getPointsToDrawInRect(DataViewController& dataViewController);
};

#endif // INCLUDED_BEZIER_SHAPE_H