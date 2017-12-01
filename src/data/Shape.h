#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>
#include "ShapeTypes.h"

class Point;

class Shape
{
protected:
   int id;
   SHAPE_TYPE::TYPE shapeType;
public:
   virtual ~Shape() {}
   Shape(int _id) : id(_id) {}

   int getId() { return id; }
   virtual int getType() = 0;
   virtual std::deque<Point*> getPoints() = 0;
};

#endif //INCLUDED_SHAPE_H