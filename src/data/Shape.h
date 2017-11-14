#pragma once
#ifndef INCLUDED_SHAPE_H
#define INCLUDED_SHAPE_H

#include <deque>

enum IDENTIFY {
    LINE = 100 ,
    BEZIER = 101,
    ARC = 110
};

class Shape
{
protected:
    IDENTIFY id;
public:
    Shape() {}
    virtual ~Shape() {}

    class Point {
    public:
        int x;
        int y;
        Point() : x(0), y(0) {}
        Point (int _x, int _y) : x(_x), y(_y) {}
    };

    virtual int getId() = 0;
    virtual std::deque<Point> getPoints() = 0;
};

#endif //INCLUDED_SHAPE_H