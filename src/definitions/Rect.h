#pragma once
#ifndef INCLUDED_RECT_H
#define INCLUDED_RECT_H

class Point;

class Rect
{
private:
   int getBiggest(int value1,int value2);
public:
   int initialX,initialY,width,height;

   Rect();
   Rect(int _initialX,int _initialY,int _width,int _height);
   Rect(int _initialX,int _initialY,float _width,float _height);

   bool fullyContained(Rect rect);

   bool isNull();
   bool operator>(const Rect size);
   Rect operator*(const float scale);
   Rect operator/(const float scale);
   Rect operator-(const Rect size);
   Rect operator+(const Rect size);
   Rect operator<<(const Rect size);
};

#endif // INCLUDED_RECT_H