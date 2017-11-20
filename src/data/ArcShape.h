#pragma once
#ifndef INCLUDED_ARC_SHAPE_H
#define INCLUDED_ARC_SHAPE_H

#include "Shape.h"

class ArcShape :
    public Shape
{
private:
    Point * center;
    Point * initial;
    Point * final;
public:
    ArcShape();
    ArcShape( Point * _center , Point * _initial , Point * _final );
    ~ArcShape();

    void setCenter( Point * _center );
    void setInitial( Point * _initial );
    void setFinal( Point * _final );

    int getId();
    std::deque<Point*> getPoints();

};

#endif // INCLUDED_ARC_SHAPE_H