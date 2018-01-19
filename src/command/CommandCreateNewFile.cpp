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
         response= ui.confirmOperation("Existe um arquivo aberto e ele não está salvo, deseja continuar mesmo assim?");
   }

   if (response) {
      std::string name= ui.showPopupNewFile();
      if (name.size() > 0) {
         File* file= new File(name);
         file->getDataViewController().setWindowSize(ui.getSizeWindow());
         data.setCurrentFile(file);

         ui.setTitleWindow(name.c_str());
         ui.setZoomScaleWidget(ZOOM::DEFAULT);
         ui.createDrawArea();
         verifyTheNeedForScrollInDrawArea(data.getCurrentFile().getDataViewController(),ui);
      }
   }
}