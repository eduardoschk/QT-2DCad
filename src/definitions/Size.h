#pragma once
#ifndef INCLUDED_SIZE_H
#define INCLUDED_SIZE_H

#include "Rect.h"

struct Size
{
public:
   Rect sizeRect;
   int width= getWidth();
   int height= getHeight();
   
   Size() : sizeRect(0,0,0,0) {}
   Size(Rect rect) : sizeRect(rect) {}
   Size(int _width,int _height) : sizeRect(Rect(0,0,_width,_height)) {}
   Size(float _width,float _height) : sizeRect(Rect(0,0,(int)_width,(int)_height)) {}

   int getWidth() { return sizeRect.width; }
   int getHeight() { return sizeRect.height; }
   bool isNull() { return sizeRect.isNull(); }

   Size operator*(float scale) { return Size(sizeRect * scale); }
   Size operator/(float scale) { return Size(sizeRect / scale); }
   Size operator+(Size size) { return Size(sizeRect + size.sizeRect); }
   Size operator-(Size size) { return Size(sizeRect - size.sizeRect); }
   bool operator>(Size size) { return sizeRect > size.sizeRect; }
};

#endif // INCLUDED_SIZE_H