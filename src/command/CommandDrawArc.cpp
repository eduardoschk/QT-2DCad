#include "CommandDrawArc.h"
#include "Data.h"
#include "UserInterface.h"
#include "Archive.h"
#include "ArcShape.h"
#include "Point.h"

CommandDrawArc::CommandDrawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 )
{
    center= new Point( x1 , y1 );
    initial= new Point( x2 , y2 );
    final= new Point( x3 , y3 );
}

CommandDrawArc::~CommandDrawArc() {}

void CommandDrawArc::exec( Data& data , UserInterface& ui )
{
    data.getCurrentArchive()->addShapeOnArchive( new ArcShape( center, initial , final ) );
}