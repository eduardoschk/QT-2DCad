#include "CommandNew.h"
#include "Data.h"
#include "UserInterface.h"

void CommandNew::exec( Data& data , UserInterface& ui ) 
{ 
    ui.createDrawArea( width , height );
    ui.setTitleWindow( pathAndFileName.c_str() );
}