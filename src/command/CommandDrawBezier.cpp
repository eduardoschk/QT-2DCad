#include "CommandDrawBezier.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"
#include "BezierShape.h"
#include "Point.h"

CommandDrawBezier::CommandDrawBezier( int xInit , int yInit , int xControl , int yControl , int xFinal , int yFinal )
{
   initial= new Point( xInit , yInit );
   control= new Point( xControl , yControl );
   final= new Point( xFinal , yFinal );
}

void CommandDrawBezier::exec( Data & data , UserInterface & ui )
{
   data.getCurrentFile().addShapeOnFile( new BezierShape( initial , control , final ) );
}