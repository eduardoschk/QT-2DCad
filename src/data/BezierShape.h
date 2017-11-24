#pragma once
#ifndef INCLUDED_BEZIER_SHAPE_H
#define INCLUDED_BEZIER_SHAPE_H

#include "Shape.h"

class BezierShape : public Shape
{
private:
   Point* initial;
   Point* control;
   Point* final;
public:
   BezierShape(Point* _initial,Point* _control,Point* _final);
   ~BezierShape();

   int getId();
   std::deque<Point*> getPoints();
};

#endif // INCLUDED_BEZIER_SHAPE_H