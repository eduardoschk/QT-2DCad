#include "BezierShape.h"

BezierShape::BezierShape() {}

BezierShape::BezierShape( Point * _initial , Point * _control , Point * _final )
{
    initial= _initial;
    control= _control;
    final=_final;
}

BezierShape::~BezierShape() {}

void BezierShape::setInitial( Point * _initial )
{
    initial= _initial;
}

void BezierShape::setControl( Point * _control )
{
    control= _control;
}

void BezierShape::setFinal( Point * _final )
{
    final= _final;
}

int BezierShape::getId()
{
    return BEZIER;
}

std::deque<Point*> BezierShape::getPoints()
{
    std::deque<Point*> points;
    points.push_back( initial );
    points.push_back( control );
    points.push_back( final );
    return points;
}