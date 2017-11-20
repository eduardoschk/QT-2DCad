#include "ArcShape.h"

ArcShape::ArcShape() :
   final( nullptr ) , center( nullptr ) , initial( nullptr ) {}

ArcShape::ArcShape( Point * _center , Point * _initial , Point * _final ) :
   final( _final ) , center( _center ) ,initial( _initial ) {}

ArcShape::~ArcShape() 
{
   delete final;
   delete center;
   delete initial;
}

void ArcShape::setCenter( Point * _center )
{
   center= _center;
}

void ArcShape::setInitial( Point * _initial )
{
   initial= _initial;
}

void ArcShape::setFinal( Point * _final )
{
   final= _final;
}

int ArcShape::getId()
{
   return ARC;
}

std::deque<Point*> ArcShape::getPoints()
{
   std::deque<Point*> points;
   points.push_back( center );
   points.push_back( initial );
   points.push_back( final );
   return points;
}