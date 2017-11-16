#include "CommandDrawLine.h"
#include "Data.h"
#include "Point.h"
#include "Archive.h"
#include "LineShape.h"

CommandDrawLine::CommandDrawLine( int x1 , int y1 , int x2 , int y2 )
{
    initial= new Point( x1 , y1 );
    final= new Point( x2 , y2 );
}

void CommandDrawLine::exec( Data& data , UserInterface& ui )
{
    data.getCurrentArchive()->addShapeOnArchive( new LineShape(initial, final) );
}