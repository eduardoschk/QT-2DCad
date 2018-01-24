#pragma once
#ifndef INCLUDED_ARC_SHAPE_H
#define INCLUDED_ARC_SHAPE_H

#include "Shape.h"

enum QUADRANT { UM,DOIS,TRES,QUATRO };

class ArcShape : public Shape
{
private:
   Coordinate originalCenterCoordinate;
   Coordinate originalInitialCoordinate;
   Coordinate originalFinalCoordinate;

   Coordinate currentCenterCoordinate;
   Coordinate currentInitialCoordinate;
   Coordinate currentFinalCoordinate;

   double radius;

   void calcRectShape();

   std::deque<Coordinate> calcCoordinatesOfShape(float scale);

   QUADRANT calcQuadrantCoordinate(const Coordinate& coordinate);
   int diffCordenates(const int coord1,const int coord2);

   void addCoordinates(std::deque<Coordinate>& coordinates,const double initAngule,const double finalAngule,float scale);

   Coordinate calcCoordinateOnAngle(double angle);

   void calcCoordinatesWithInitialCoordinateInFirstQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale);
   void calcCoordinatesWithInitialCoordinateInSecondQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale);
   void calcCoordinatesWithInitialCoordinateInThirdQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale);
   void calcCoordinatesWithInitialCoordinateInFourthQuadrant(std::deque<Coordinate>& coordinates,double distanceInitFinal,float scale);

   double calcAngle(double catetoOposto,double hipo);
   double calcPythagoras(const Coordinate& Coordinate1,const Coordinate& Coordinate2);
public:
   ~ArcShape();
   ArcShape(int _id, Coordinate& _center,Coordinate& _initial,Coordinate& _final);

   int getType();

   Rect getRectShape();
   Rect getCurrentRectShape(DataViewController& dataViewController);

   std::deque<Coordinate> getSelectedCoordinates();
   std::deque<Coordinate> getCoordinatesToDraw(DataViewController& dataViewController);
   std::deque<Coordinate> getCoordinatesToDrawInRect(DataViewController& dataViewController);

};

#endif // INCLUDED_ARC_SHAPE_H