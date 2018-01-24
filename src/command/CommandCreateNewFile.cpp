#include "CommandCreateNewFile.h"
#include "Data.h"
#include "File.h"
#include "ZoomControl.h"
#include "UserInterface.h"

void CommandCreateNewFile::exec(Data& data,UserInterface& ui)
{
   bool response= true;
   if (data.hasFile()) {
      if (!data.getCurrentFile().isSaved())
         response= ui.confirmOperation("There's a file open and it's not save, do you want to continue?");
   }

   while (response) {
      try {
         std::string name= ui.showPopupNewFile();
         if (name.size() > 0) {
            File* file= new File(name);
            file->getDataViewController().setWindowSize(ui.getSizeWindow());
            data.setCurrentFile(file);

            ui.createDrawArea();
            ui.setTitleWindow(name.c_str());
            ui.setZoomScaleWidget(ZOOM::DEFAULT);
            ui.setTipMessage("Select the shape");
            verifyTheNeedForScrollInDrawArea(data.getCurrentFile().getDataViewController(),ui);
            break;
         }
         else
            ui.showErrorMessage("File name can not be empty");
      }
      catch (UserInterface::CancelNewFile ex) {
         break;
      }
   }
}