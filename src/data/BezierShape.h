#pragma once
#ifndef INCLUDED_BEZIER_SHAPE_H
#define INCLUDED_BEZIER_SHAPE_H

#include "Shape.h"

class BezierShape :
    public Shape
{
public:
    BezierShape();
    virtual ~BezierShape();
};

#endif // INCLUDED_BEZIER_SHAPE_H