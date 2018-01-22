#include "Rect.h"
#include "Point.h"

#include <iostream>

Rect::Rect() : initialX(0),initialY(0),height(0),width(0) {}

Rect::Rect(int _initialX,int _initialY,int _width,int _height) : initialX(_initialX),initialY(_initialY),width(_width),height(_height) {}

Rect::Rect(int _initialX,int _initialY,float _width,float _height) : initialX(_initialX),initialY(_initialY),width((int)_width),height((int)_height) {}

///////////////////////////////////////////////////////////////////////////////

int Rect::getBiggest(int value1,int value2)
{ 
   return (value1 > value2) ? value1 : value2; 
}

///////////////////////////////////////////////////////////////////////////////

bool Rect::fullyContained(Rect rect)
{ 
   return (initialX <= rect.initialX && initialY <= rect.initialY && (initialX + width >= rect.initialX + rect.width) && (initialY + height >= rect.initialY + rect.height)); 
}

bool Rect::partiallyContained(Rect rect)
{
   return true;
}

bool Rect::isNull()
{ 
   return (height <= 0) && (width <= 0); 
}

///////////////////////////////////////////////////////////////////////////////

bool Rect::operator>(const Rect size)
{ 
   return (width * height) > (size.width * size.height); 
}

Rect Rect::operator*(const float scale)
{ 
   return Rect(initialX,initialY,width * scale,height * scale); 
}

Rect Rect::operator/(const float scale)
{ 
   return Rect(initialX,initialY,width / scale,height / scale); 
}

Rect Rect::operator-(const Rect size)
{ 
   return Rect(initialX,initialY,width - size.width,height - size.height); 
}

Rect Rect::operator+(const Rect size)
{ 
   return Rect(initialX,initialY,width + size.width,height + size.height); 
}

Rect Rect::operator<<(const Rect size)
{ 
   return Rect(initialX,initialY,getBiggest((size.initialX + size.width),width),getBiggest((size.initialY + size.height),height)); 
}
