#include "CommandSaveAs.h"
#include "Data.h"
#include "UserInterface.h"
#include "Archive.h"
#include <string>

void CommandSaveAs::exec( Data& data , UserInterface& ui ) 
{
    std::string t = ui.requestPathFileToSave( data.getCurrentArchive()->getArchiveName() );
}