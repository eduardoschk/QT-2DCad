#pragma once
#ifndef INCLUDED_COORDINATE_MAPPER_H
#define INCLUDED_COORDINATE_MAPPER_H

#include "Size.h"
#include "Coordinate.h"

class CoordinateMapper
{
private:
   Size worldSize;
   Size deviceSize;

public:
   ~CoordinateMapper() {}
   CoordinateMapper(Size& worldSize, Size& deviceSize);

   Coordinate mapCoordinateWorldToDevice(Coordinate& coordinate);
   Coordinate mapCoordinateDeviceToWorld(Coordinate& coordinate);

   Size& getWorldSize();
   Size& getDeviceSize();
   void setWorldSize(Size& size);
   void setDeviceSize(Size& size);
};

#endif // INCLUDED_COORDENATE_MAPPER_H