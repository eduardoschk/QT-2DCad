#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>

enum IDENTIFY {
    LINE = 100 ,
    BEZIER = 101,
    ARC = 110
};

class Point;

class Shape
{
protected:
   IDENTIFY id;
public:
   Shape() {}
   virtual ~Shape() {}

   virtual int getId() = 0;
   virtual std::deque<Point*> getPoints() = 0;
};

#endif //INCLUDED_SHAPE_H