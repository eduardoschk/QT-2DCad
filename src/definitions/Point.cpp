#include "Point.h"
#include "Rect.h"

Point::Point() : x(0),y(0) {}

Point::Point(int _x,int _y) : x(_x),y(_y) {}

Point::Point(float _x,float _y) : x((int)_x),y((int)_y) {}

Point::Point(double _x,double _y) : x((int)_x),y((int)_y) {}

///////////////////////////////////////////////////////////////////////////////

bool Point::isNull() 
{ 
   return (x <= 0) && (y <= 0); 
}

bool Point::on(Rect rect) 
{ 
   return !((x < rect.initialX) || (y < rect.initialY) || (y >(rect.initialY + rect.height)) || (x >(rect.initialX + rect.width))); 
}

///////////////////////////////////////////////////////////////////////////////

Point Point::operator*(float scale) 
{
   return Point(x*scale,y*scale); 
}

Point Point::operator/(float scale) 
{ 
   return Point(x / scale,y / scale); 
}

Point Point::operator-(Point point)
{ 
   return Point(x - point.x,y - point.y); 
}