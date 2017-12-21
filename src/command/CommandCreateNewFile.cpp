#include "CommandCreateNewFile.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"
#include "NewFileStructure.h"

void CommandCreateNewFile::exec(Data& data,UserInterface& ui)
{
   bool response= true;
   if (data.hasFile()) {
      if (!data.getCurrentFile().isSaved())
         response= ui.confirmOperation("Existe um file aberto e ele não está salvo, deseja continuar mesmo assim?");
   }

   if (response) {
      NEW_FILE_STRUCTURE nfs= ui.showPopupNewFile();
      if (nfs.isValid()) {
         File* archive= new File(nfs.name,nfs.width,nfs.height);
         data.setCurrentFile(archive);

         ui.createDrawArea(nfs.width,nfs.height);
         ui.setTitleWindow(nfs.name.c_str());
      }
   }
}