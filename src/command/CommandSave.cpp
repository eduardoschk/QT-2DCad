#include "CommandSave.h"
#include "Data.h"
#include "UserInterface.h"
#include "Archive.h"

void CommandSave::exec( Data& data , UserInterface& ui ) 
{
    data.getCurrentArchive()->save("C:/Users/eduardo.kreuch/Desktop");
}