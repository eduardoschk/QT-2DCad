#include "PointerMapper.h"

PointerMapper::PointerMapper()
{

}

///////////////////////////////////////////////////////////////////////////////

Point PointerMapper::fixPoint(Point point)
{
   //point.x-= rectPresentation.initialX;
   //point.y-= rectPresentation.initialY;
   //return point;
}

Point PointerMapper::mapPointWorldToDevice(Point point)
{
   Point devicePoint;

   devicePoint.x= point.x * (deviceRect.width / worldSize.width);
   devicePoint.y= point.y * (deviceRect.height / worldSize.height);

   return devicePoint;
}


Point PointerMapper::mapPointDeviceToWorld(Point point)
{
   Point worldPoint;

   worldPoint.x= point.x * (worldSize.width) / deviceRect.width;
   worldPoint.y= point.y * (worldSize.height) / deviceRect.height;
   
   return worldPoint;
}