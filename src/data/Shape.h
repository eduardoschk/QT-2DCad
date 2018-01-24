#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>
#include "Coordinate.h"
#include "ShapeTypes.h"
#include "Rect.h"

class DataViewController;

class Shape
{
protected:
   int id;
   Rect rectShape;

   virtual void calcRectShape() = 0;

public:
   virtual ~Shape() {}
   Shape(int _id) : id(_id) {}

   int getId() { return id; }
   virtual int getType() = 0;

   virtual Rect getRectShape() = 0;
   virtual Rect getCurrentRectShape(DataViewController& dataViewController) = 0;

   virtual std::deque<Coordinate> getSelectedCoordinates() = 0;
   virtual std::deque<Coordinate> getCoordinatesToDraw(DataViewController& dataViewController) = 0;
   virtual std::deque<Coordinate> getCoordinatesToDrawInRect(DataViewController& dataViewController) = 0;
};

#endif //INCLUDED_SHAPE_H