#include "CommandResizeWindow.h"
#include "Data.h"
#include "File.h"
#include "Size.h"
#include "UserInterface.h"

CommandResizeWindow::CommandResizeWindow(Size& _size) : size(_size) {}

void CommandResizeWindow::exec(Data& data,UserInterface& ui)
{
   DataViewController& dataViewController=  data.getCurrentFile().getDataViewController();

   if (data.hasFile()) {
      dataViewController.setWindowSize(size);
      
      verifyTheNeedForScrollInDrawArea(dataViewController,ui);

      repaint(data,ui);
   }
}