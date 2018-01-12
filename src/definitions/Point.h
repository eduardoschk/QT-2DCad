#pragma once
#ifndef INCLUDED_POINT_H
#define INCLUDED_POINT_H

#include "Rect.h"

struct Point {
public:
    int x,y;

    Point() : x(0),y(0) {}
    Point(int _x,int _y) : x(_x),y(_y) {}
    Point(float _x,float _y) : x((int)_x),y((int)_y) {}
    Point(double _x,double _y) : x((int)_x),y((int)_y) {}
    
    bool isNull() { return (x <= 0) && (y <= 0); }
    bool on(Rect rect) { return !((x < rect.initialX) || (y < rect.initialY) || (y >(rect.initialY + rect.height)) || (x >(rect.initialX + rect.width))); }

    Point operator*(float scale) { return Point(x*scale,y*scale); }
    Point operator/(float scale) { return Point(x/scale,y/scale); }

};

#endif // INCLUDED_POINT_H