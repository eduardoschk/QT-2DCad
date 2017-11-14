#include "LineShape.h"

LineShape::LineShape() {}

LineShape::LineShape( Point _initial , Point _final )
{
    initial= _initial;
    final= _final;
}

LineShape::~LineShape() {}

void LineShape::setInitial( Point _initial )
{
    initial= _initial;
}

void LineShape::setFinal( Point _final )
{
    final= _final;
}

int LineShape::getId()
{
    return LINE;
}

std::deque<Shape::Point> LineShape::getPoints()
{
    std::deque<Shape::Point> points;
    points.push_back( initial );
    points.push_back( final );
    return points;
}
