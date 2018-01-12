#include "CommandCreateNewFile.h"
#include "Data.h"
#include "File.h"
#include "ZoomControl.h"
#include "UserInterface.h"
#include "NewFileStructure.h"

void CommandCreateNewFile::exec(Data& data,UserInterface& ui)
{
   bool response= true;
   if (data.hasFile()) {
      if (!data.getCurrentFile().isSaved())
         response= ui.confirmOperation("Existe um arquivo aberto e ele não está salvo, deseja continuar mesmo assim?");
   }

   if (response) {
      NEW_FILE_STRUCTURE nfs= ui.showPopupNewFile();
      if (nfs.isValid()) {
         File* file= new File(nfs.name,nfs.size);
         file->getDataViewController().setWindowSize(ui.getSizeWindow());
         data.setCurrentFile(file);

         ui.setTitleWindow(nfs.name.c_str());
         ui.setZoomScaleWidget(ZOOM::DEFAULT);
         ui.createDrawArea(file->getDataViewController().getViewPortSize());
      }
   }
}