#include "CommandDrawLine.h"
#include "Data.h"
#include "Point.h"
#include "File.h"
#include "LineShape.h"

CommandDrawLine::CommandDrawLine( int xInit , int yInit , int xFinal , int yFinal )
{
   initial= new Point( xInit , yInit );
   final= new Point( xFinal , yFinal );
}

void CommandDrawLine::exec( Data& data , UserInterface& ui )
{
   data.getCurrentFile().addShapeOnFile( new LineShape(initial, final) );
}