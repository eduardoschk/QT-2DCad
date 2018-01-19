#pragma once
#ifndef INCLUDED_POINT_H
#define INCLUDED_POINT_H

class Rect;

class Point {
public:
    int x,y;

    ~Point() {}
    Point();
    Point(int _x,int _y);
    Point(float _x,float _y);
    Point(double _x,double _y);
    
    bool isNull();
    bool on(Rect rect);

    Point operator*(float scale);
    Point operator/(float scale);
    Point operator-(Point point);
};

#endif // INCLUDED_POINT_H