#include "CoordinateMapper.h"

CoordinateMapper::CoordinateMapper(Size& _worldSize,Size& _deviceSize)
{
   worldSize= _worldSize;
   deviceSize= _deviceSize;
}

///////////////////////////////////////////////////////////////////////////////

Coordinate CoordinateMapper::mapCoordinateWorldToDevice(Coordinate& coordinate)
{
   Coordinate deviceCoordinate;
   deviceCoordinate.x= (coordinate.x * deviceSize.width) / worldSize.width;
   deviceCoordinate.y= (coordinate.y * deviceSize.height) / worldSize.height;
   return deviceCoordinate;
}

Coordinate CoordinateMapper::mapCoordinateDeviceToWorld(Coordinate& coordinate)
{
   Coordinate worldCoordinate;
   worldCoordinate.x= (coordinate.x * worldSize.width) / deviceSize.width;
   worldCoordinate.y= (coordinate.y * worldSize.height) / deviceSize.height;
   return worldCoordinate;
}

///////////////////////////////////////////////////////////////////////////////

Size& CoordinateMapper::getWorldSize()
{
   return worldSize;
}

Size& CoordinateMapper::getDeviceSize()
{
   return deviceSize;
}

void CoordinateMapper::setWorldSize(Size& size)
{
   worldSize= size;
}

void CoordinateMapper::setDeviceSize(Size& size)
{
   deviceSize= size;
}

///////////////////////////////////////////////////////////////////////////////
