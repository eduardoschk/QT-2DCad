#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>
#include "ShapeIdentifier.h"

class Point;

class Shape
{
protected:
   SHAPE_ID::IDENTIFIER id;
public:
   Shape() {}
   virtual ~Shape() {}

   virtual int getId() = 0;
   virtual std::deque<Point*> getPoints() = 0;
};

#endif //INCLUDED_SHAPE_H