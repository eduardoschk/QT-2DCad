#include "Coordinate.h"
#include "Rect.h"

Coordinate::Coordinate() : x(0),y(0) {}

Coordinate::Coordinate(int _x,int _y) : x(_x),y(_y) {}

Coordinate::Coordinate(float _x,float _y) : x((int)_x),y((int)_y) {}

Coordinate::Coordinate(double _x,double _y) : x((int)_x),y((int)_y) {}

///////////////////////////////////////////////////////////////////////////////

bool Coordinate::isNull() 
{ 
   return (x <= 0) && (y <= 0); 
}

bool Coordinate::on(Rect rect) 
{ 
   return !((x < rect.initialX) || (y < rect.initialY) || (y >(rect.initialY + rect.height)) || (x >(rect.initialX + rect.width))); 
}

///////////////////////////////////////////////////////////////////////////////

Coordinate Coordinate::operator*(float scale) 
{
   return Coordinate(x*scale,y*scale); 
}

Coordinate Coordinate::operator/(float scale) 
{ 
   return Coordinate(x / scale,y / scale); 
}

Coordinate Coordinate::operator-(Coordinate& coordinate)
{ 
   return Coordinate(x - coordinate.x,y - coordinate.y);
}