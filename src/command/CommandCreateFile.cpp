#include "CommandCreateFile.h"
#include "Data.h"
#include "File.h"
#include "UserInterface.h"

void CommandCreateFile::exec( Data & data , UserInterface & ui)
{
   File * archive = new File( path , width , height );
   data.setCurrentFile( archive );

   ui.createDrawArea( width , height );
   ui.setTitleWindow( path.c_str() );
}