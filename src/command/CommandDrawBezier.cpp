#include "CommandDrawBezier.h"
#include "Data.h"
#include "UserInterface.h"
#include "Archive.h"
#include "BezierShape.h"
#include "Point.h"


CommandDrawBezier::CommandDrawBezier( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 )
{
    initial= new Point( x1 , y1 );
    control= new Point( x2 , y2 );
    final= new Point( x3 , y3 );
}

void CommandDrawBezier::exec( Data& data , UserInterface& ui )
{
    data.getCurrentArchive()->addShapeOnArchive( new BezierShape( initial , control , final ) );
}