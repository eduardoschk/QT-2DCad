#include "CommandSaveFile.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"

void CommandSaveFile::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      if (!data.getCurrentFile().alreadySaved()) {
         std::string path= ui.requestPathFileToSave(data.getCurrentFile().getFileName());
         if (path.size() > 0) {
            FileParams pathAndFile= dividerNameOfPath(path);
            data.getCurrentFile().setPath(pathAndFile.path);
            data.getCurrentFile().setFileName(pathAndFile.name);
            data.save();
         }
      }
      else
         data.save();
   }
   else
      ui.showErrorMessage("Não existe arquivo para ser salvo");
}