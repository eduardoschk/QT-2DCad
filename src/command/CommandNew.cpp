#include "CommandNew.h"
#include "Data.h"
#include "Archive.h"
#include "UserInterface.h"

void CommandNew::exec( Data& data , UserInterface& ui ) 
{ 
    Archive * archive = new Archive( fileName , width, height);
    data.setCurrentArchive( archive );

    ui.createDrawArea( width , height );
    ui.setTitleWindow( fileName.c_str() );
}