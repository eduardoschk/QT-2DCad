#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>
#include "Point.h"
#include "ShapeTypes.h"

class Rect;
class DataViewController;

class Shape
{
protected:
   int id;

public:
   virtual ~Shape() {}
   Shape(int _id) : id(_id) {}

   int getId() { return id; }
   virtual int getType() = 0;

   virtual Rect getOriginalRectShape() = 0;
   virtual Rect getCurrentRectShape(DataViewController& dataViewController) = 0;

   virtual std::deque<Point> getSelectedPoints() = 0;
   virtual std::deque<Point> getPointsToDraw(DataViewController& dataViewController) = 0;
   virtual std::deque<Point> getPointsToDrawInRect(DataViewController& dataViewController) = 0;
};

#endif //INCLUDED_SHAPE_H