#include "CommandSave.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"

void CommandSave::exec( Data& data , UserInterface& ui ) 
{
   if ( &data.getCurrentFile() ) {
      if ( data.getCurrentFile().getPath().size() == 0 ) {
         std::string path= ui.requestPathFileToSave( data.getCurrentFile().getFileName() );
         if ( path.size() > 0 ) {
            FileParams pathAndFile= dividerNameOfPath( path );
            data.getCurrentFile().setPath( pathAndFile.path );
            data.getCurrentFile().setFileName( pathAndFile.name );
            data.getCurrentFile().save();
         }
      }
      else 
         data.getCurrentFile().save();
   }
   else
      ui.showErrorMessage( "Não existe arquivo para ser salvo" );
}