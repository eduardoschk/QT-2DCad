#pragma once
#ifndef INCLUDED_LINE_SHAPE_H
#define INCLUDED_LINE_SHAPE_H

#include "Shape.h"
class Point;

class LineShape : public Shape
{
private:
   Point* initial;
   Point* final;
public:
   LineShape(Point* _initial,Point* _final);
   ~LineShape();

   int getId();
   std::deque<Point*> getPoints();
};

#endif // INCLUDED_LINE_SHAPE_H