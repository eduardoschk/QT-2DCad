#pragma once
#ifndef INCLUDED_LINE_SHAPE_H
#define INCLUDED_LINE_SHAPE_H

#include "Shape.h"

class LineShape : public Shape
{
private:
   Coordinate originalInitialCoordinate;
   Coordinate originalFinalCoordinate;

   Coordinate currentInitialCoordinate;
   Coordinate currentFinalCoordinate;

   void calcRectShape();
   std::deque<Coordinate> calcCoordinatesOfShape(float scale);
public:
   ~LineShape() {}
   LineShape(int _id,Coordinate& _initial,Coordinate& _final);

   int getType();

   Rect getRectShape();
   Rect getCurrentRectShape(DataViewController& dataViewController);

   std::deque<Coordinate> getSelectedCoordinates();
   std::deque<Coordinate> getCoordinatesToDraw(DataViewController& dataViewController);
   std::deque<Coordinate> getCoordinatesToDrawInRect(DataViewController& dataViewController);
};

#endif // INCLUDED_LINE_SHAPE_H