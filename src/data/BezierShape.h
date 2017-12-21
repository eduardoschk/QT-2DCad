#pragma once
#ifndef INCLUDED_BEZIER_SHAPE_H
#define INCLUDED_BEZIER_SHAPE_H

#include "Point.h"
#include "Shape.h"

class BezierShape : public Shape
{
private:
   Point initial;
   Point control;
   Point final;
public:
   ~BezierShape();
   BezierShape(int _id,Point _initial,Point _control,Point _final);

   int getType();
   std::deque<Point> getPoints();
};

#endif // INCLUDED_BEZIER_SHAPE_H