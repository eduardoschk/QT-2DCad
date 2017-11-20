#include "CommandDrawArc.h"
#include "Data.h"
#include "UserInterface.h"
#include "file.h"
#include "ArcShape.h"
#include "Point.h"

CommandDrawArc::CommandDrawArc( int xCenter , int yCenter , int xInit , int yInit , int xFinal , int yFinal )
{
   initial= new Point( xInit , yInit );
   final= new Point( xFinal , yFinal );
   center= new Point( xCenter , yCenter );
}

void CommandDrawArc::exec( Data& data , UserInterface& ui )
{
   data.getCurrentFile().addShapeOnFile( new ArcShape( center, initial , final ) );
}