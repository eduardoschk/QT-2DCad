#pragma once
#ifndef INCLUDED_POINT_H
#define INCLUDED_POINT_H

class Point {
public:
    int x;
    int y;

    Point() : x( 0 ) , y( 0 ) {}
    Point( int _x , int _y ) : x( _x ) , y( _y ) {}
    ~Point() {}

    bool isNull() { return x > 0 && y > 0; }
};

#endif // INCLUDED_POINT_H