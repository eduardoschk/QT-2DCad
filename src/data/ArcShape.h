#pragma once
#ifndef INCLUDED_ARC_SHAPE_H
#define INCLUDED_ARC_SHAPE_H

#include "Shape.h"

enum QUADRANT { UM,DOIS,TRES,QUATRO };

class ArcShape : public Shape
{
private:
   Point& originalCenterPoint;
   Point& originalInitialPoint;
   Point& originalFinalPoint;

   Point currentCenterPoint;
   Point currentInitialPoint;
   Point currentFinalPoint;

   double raio;

   Rect calcRectShape(float scale);
   std::deque<Point> calcPointsToDraw(float scale);

   QUADRANT calcQuadrantPoint(const Point& point);
   int diffCordenates(const int coord1,const int coord2);

   void drawPoints(std::deque<Point>& points,const double initAngule,const double finalAngule,float scale);

   Point calcPointOnAngle(double angle);

   void drawWithInitialPointInFirstQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale);
   void drawWithInitialPointInSecondQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale);
   void drawWithInitialPointInThirdQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale);
   void drawWithInitialPointInFourthQuadrant(std::deque<Point>& points,double distanceInitFinal,float scale);

   double calcAngle(double catetoOposto,double hipo);
   double calcPitagoras(const Point point1,const Point point2);
public:
   ~ArcShape();
   ArcShape(int _id, Point& _center,Point& _initial,Point& _final);

   int getType();

   Rect getOriginalRectShape();
   Rect getCurrentRectShape(DataViewController& dataViewController);

   std::deque<Point> getSelectedPoints();
   std::deque<Point> getPointsToDraw(DataViewController& dataViewController);
   std::deque<Point> getPointsToDrawInRect(DataViewController& dataViewController);

};

#endif // INCLUDED_ARC_SHAPE_H