#include "CommandSaveAsFile.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"
#include <string>

void CommandSaveAsFile::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile())
      data.saveAs(ui.requestPathFileToSave(data.getCurrentFile().getFileName()));
   else
      ui.showErrorMessage("Não existe arquivo para ser salvo");
}