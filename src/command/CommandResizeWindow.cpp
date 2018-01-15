#include "CommandResizeWindow.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

CommandResizeWindow::CommandResizeWindow(Size _size)
{
   size= _size;
}

void CommandResizeWindow::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      data.getCurrentFile().getDataViewController().setWindowSize(size);
      
      resizeDrawArea(data.getCurrentFile().getDataViewController(),ui);
      verifyTheNeedForScrollInDrawArea(data.getCurrentFile().getDataViewController(),ui);

      repaint(data,ui);
   }
}