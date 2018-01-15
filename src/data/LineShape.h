#pragma once
#ifndef INCLUDED_LINE_SHAPE_H
#define INCLUDED_LINE_SHAPE_H

#include "Shape.h"
#include "Point.h"

class LineShape : public Shape
{
private:
   Point initial;
   Point final;
public:
   ~LineShape() {}
   LineShape(int _id,Point _initial,Point _final);

   int getType();

   std::deque<Point> getSelectedPoints();
   std::deque<Point> getPointsToDraw(float scale);
   std::deque<Point> getPointsToDrawInRect(float scale,Rect rect);
};

#endif // INCLUDED_LINE_SHAPE_H