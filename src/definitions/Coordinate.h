#pragma once
#ifndef INCLUDED_COORDINATE_H
#define INCLUDED_COORDINATE_H

class Rect;

class Coordinate {
public:
    int x,y;

    ~Coordinate() {}
    Coordinate();
    Coordinate(int _x,int _y);
    Coordinate(float _x,float _y);
    Coordinate(double _x,double _y);
    
    bool isNull();
    bool on(Rect rect);

    Coordinate operator*(float scale);
    Coordinate operator/(float scale);
    Coordinate operator-(Coordinate& Coordenate);
};

#endif // INCLUDED_COORDENATE_H