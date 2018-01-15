#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>
#include "Point.h"
#include "ShapeTypes.h"

class Shape
{
protected:
   int id;
public:
   virtual ~Shape() {}
   Shape(int _id) : id(_id) {}

   int getId() { return id; }
   virtual int getType() = 0;

   virtual std::deque<Point> getSelectedPoints() = 0;
   virtual std::deque<Point> getPointsToDraw(float scale) = 0;
   virtual std::deque<Point> getPointsToDrawInRect(float scale,Rect rect) = 0;
};

#endif //INCLUDED_SHAPE_H