#pragma once
#ifndef INCLUDED_RECT_H
#define INCLUDED_RECT_H

struct Rect
{
public:
   int initialX,initialY,width,height;

   Rect() : initialX(0),initialY(0),height(0),width(0) {}
   Rect(int _initialX,int _initialY,int _width,int _height) : initialX(_initialX),initialY(_initialY),width(_width),height(_height) {}
   Rect(int _initialX,int _initialY,float _width,float _height) : initialX(_initialX),initialY(_initialY),width((int)_width),height((int)_height) {}

   bool isNull() { return (height <= 0) && (width <= 0); }

   Rect operator*(float scale) { return Rect(initialX,initialY,width * scale,height * scale); }
   Rect operator/(float scale) { return Rect(initialX,initialY,width / scale,height / scale); }
   Rect operator+(Rect size) { return Rect(initialX,initialY,width + size.width,height + size.height); }
   Rect operator-(Rect size) { return Rect(initialX,initialY,width - size.width,height - size.height); }
   bool operator>(Rect size) { return (width * height) > (size.width * size.height); }
};

#endif // INCLUDED_RECT_H