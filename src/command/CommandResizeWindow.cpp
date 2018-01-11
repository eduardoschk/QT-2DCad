#include "CommandResizeWindow.h"
#include "Data.h"
#include "Size.h"
#include "File.h"
#include "UserInterface.h"

CommandResizeWindow::CommandResizeWindow(int _width,int _height)
{
   width= _width;
   height= _height;
}

void CommandResizeWindow::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      data.getCurrentFile().getDataViewController().setWindowSize(Size(width,height));
      ui.setSizeDrawArea(data.getCurrentFile().getDataViewController().getViewPortSize());
   }
}