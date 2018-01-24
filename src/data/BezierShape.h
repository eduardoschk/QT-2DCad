#pragma once
#ifndef INCLUDED_BEZIER_SHAPE_H
#define INCLUDED_BEZIER_SHAPE_H

#include "Shape.h"

class BezierShape : public Shape
{
private:
   Coordinate originalInitialCoordinate;
   Coordinate originalControlCoordinate;
   Coordinate originalFinalCoordinate;

   Coordinate currentInitialCoordinate;
   Coordinate currentControlCoordinate;
   Coordinate currentFinalCoordinate;

   void calcRectShape();
   std::deque<Coordinate> calcCoordinatesOfShape(float scale);

   float calcX(float distance);
   float calcY(float distance);
   Coordinate calcCoordinate(float distance);

public:
   ~BezierShape() {}
   BezierShape(int _id,Coordinate& _initial,Coordinate& _control,Coordinate& _final);

   int getType();

   Rect getRectShape();
   Rect getCurrentRectShape(DataViewController& dataViewController);

   std::deque<Coordinate> getSelectedCoordinates();
   std::deque<Coordinate> getCoordinatesToDraw(DataViewController& dataViewController);
   std::deque<Coordinate> getCoordinatesToDrawInRect(DataViewController& dataViewController);
};

#endif // INCLUDED_BEZIER_SHAPE_H