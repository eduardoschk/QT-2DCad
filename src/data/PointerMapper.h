#pragma once
#ifndef INCLUDED_POINTER_MAPPER_H
#define INCLUDED_POINTER_MAPPER_H

#include "Point.h"
#include "Rect.h"
#include "Size.h"

class PointerMapper
{
private:
   Size worldSize;
   Rect deviceRect;
public:
   PointerMapper();
   ~PointerMapper() {}

   Point fixPoint(Point point);
   Point mapPointWorldToDevice(Point point);
   Point mapPointDeviceToWorld(Point point);
};

#endif // INCLUDED_POINTER_MAPPER_H