#include "Size.h"
#include "Rect.h"

Size::Size(Rect& rect) : sizeRect(rect) {}

Size::Size() : sizeRect(Rect(0,0,0,0)) {}

Size::Size(int _width,int _height) : sizeRect(Rect(0,0,_width,_height)) {}

Size::Size(float _width,float _height) : sizeRect(Rect(0,0,(int)_width,(int)_height)) {}

///////////////////////////////////////////////////////////////////////////////

int Size::getWidth() 
{ 
   return sizeRect.width; 
}

int Size::getHeight() 
{ 
   return sizeRect.height; 
}

bool Size::isNull() 
{ 
   return sizeRect.isNull(); 
}

bool Size::contains(const Rect& rect) 
{ 
   return (rect.width + rect.initialX <= sizeRect.width && rect.height + rect.initialY <= sizeRect.height); 
}

///////////////////////////////////////////////////////////////////////////////

Size Size::operator=(const Size& size)
{
   return Size(size);
}

Size Size::operator<<(const Rect& rect)
{
   return Size(sizeRect << rect);
}

bool Size::operator!=(const Size& size)
{
   return width != size.width || height != size.height;
}

Size Size::operator+(const Rect& rect)
{
   return Size(sizeRect + rect);
}

Size Size::operator*(const float& scale)
{
   return Size(sizeRect * scale);
}

Size Size::operator/(const float& scale)
{
   return Size(sizeRect / scale);
}

bool Size::operator>(const Size& size)
{
   return sizeRect > size.sizeRect;
}

Size Size::operator+(const Size& size)
{
   return Size(sizeRect + size.sizeRect);
}

Size Size::operator-(const Size& size)
{
   return Size(sizeRect - size.sizeRect);
}