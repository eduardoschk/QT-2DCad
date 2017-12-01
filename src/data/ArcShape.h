#pragma once
#ifndef INCLUDED_ARC_SHAPE_H
#define INCLUDED_ARC_SHAPE_H

#include "Shape.h"
#include "Point.h"

class ArcShape : public Shape
{
private:
   Point* center;
   Point* initial;
   Point* final;
public:
   ArcShape(int _id, Point* _center,Point* _initial,Point* _final);
   ~ArcShape();

   int getType();
   std::deque<Point*> getPoints();

};

#endif // INCLUDED_ARC_SHAPE_H