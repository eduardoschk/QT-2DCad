#pragma once
#ifndef INCLUDED_DATA_VIEW_CONTROLLER_H
#define INCLUDED_DATA_VIEW_CONTROLLER_H

class DataViewController
{
private:
   int currentScaleZoom;
   const int footerHeight= 100;
   int previewStartingPointWidth;
   int previewStartingPointHeight;
public:
   ~DataViewController() {}
   DataViewController() {}
};

#endif // INCLUDED_DATA_VIEW_CONTROLLER_H