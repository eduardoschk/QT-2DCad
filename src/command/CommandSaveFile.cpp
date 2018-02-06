#include "CommandSaveFile.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandSaveFile::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      File& currentFile= data.getCurrentFile();
      if (!currentFile.alreadySaved()) {
         std::string path= ui.requestPathFileToSave(currentFile.getFileName());
         if (path.size() > 0) {
            FileParams pathAndFile= getNameAndFolderPathOfAbsolutePath(path);
            currentFile.setPath(pathAndFile.path);
            currentFile.setFileName(pathAndFile.name);
            data.save();
         }
      }
      else
         data.save();
   }
   else
      ui.showErrorMessage("There aren't files open");
}