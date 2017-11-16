#pragma once
#ifndef INCLUDED_BEZIER_SHAPE_H
#define INCLUDED_BEZIER_SHAPE_H

#include "Shape.h"

class BezierShape :
    public Shape
{
private:
    Point * initial;
    Point * control;
    Point * final;
public:
    BezierShape();
    BezierShape( Point * _initial , Point * _control , Point * _final );
    virtual ~BezierShape();

    void setInitial( Point * _initial );
    void setControl( Point * _control);
    void setFinal( Point * _final );

    int getId();
    std::deque<Point*> getPoints();
};

#endif // INCLUDED_BEZIER_SHAPE_H