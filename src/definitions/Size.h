#pragma once
#ifndef INCLUDED_SIZE_H
#define INCLUDED_SIZE_H

#include "Rect.h"

class Size
{
private:
   Size(Rect& rect);
public:
   Rect sizeRect;
   int width= getWidth();
   int height= getHeight();

   Size();
   Size(int _width,int _height);
   Size(float _width,float _height);

   int getWidth();
   int getHeight();
   bool isNull();
   bool contains(const Rect& rect);

   Size operator<<(const Rect& rect);
   bool operator!=(const Size& size);
   Size operator+(const Rect& rect);
   Size operator*(const float& scale);
   Size operator/(const float& scale);
   bool operator>(const Size& size);
   Size operator+(const Size& size);
   Size operator-(const Size& size);
};

#endif // INCLUDED_SIZE_H