#include "CommandCreateNewFile.h"
#include "Data.h"
#include "File.h"
#include "ZoomControl.h"
#include "UserInterface.h"

bool CommandCreateNewFile::checkIfCanCreateFile(Data& data,UserInterface& ui)
{
   bool response= true;
   if (data.hasFile() && !data.getCurrentFile().isSaved())
      response= ui.confirmOperation("There's a file open and it's not save, do you want to continue?");
   return response;
}

void CommandCreateNewFile::configDrawArea(DataViewController& viewController,UserInterface& ui)
{
   ui.createDrawArea();
   ui.markOffAllOptions();
   ui.setZoomScaleWidget(ZOOM::DEFAULT);
   ui.setTipMessage("Select the shape");
   ui.setTitleWindow(file->getFileName().c_str());

   verifyTheNeedForScrollInDrawArea(viewController,ui);
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateNewFile::exec(Data& data,UserInterface& ui)
{
   while (checkIfCanCreateFile(data,ui)) {
      try {
         std::string name= ui.showPopupNewFile();
         if (name.size() > 0) {
            file= new File(name);
            file->getDataViewController().setWindowSize(ui.getSizeWindow());
            data.setCurrentFile(file);

            configDrawArea(data.getCurrentFile().getDataViewController(),ui);
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