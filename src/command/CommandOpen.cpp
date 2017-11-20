#include "CommandOpen.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"
#include "Shape.h"
#include "Point.h"

void CommandOpen::exec( Data& data , UserInterface& ui )
{
   File * file = new File();
   std::string completedPath= ui.requestPathFileToOpen();
   file= file->open( completedPath );

   FileParams params= dividerNameOfPath( completedPath );
   file->setPath( params.path );
   file->setFileName( params.name );

   data.setCurrentFile( file );

   ui.createDrawArea( file->getWidth(), file->getHeight() );

   std::deque<Shape*> shapes= file->getShapes();
   for ( int i= 0 ; i < shapes.size() ; ++i )
      drawShape(ui, *shapes[i]);
}

void CommandOpen::drawShape( UserInterface & ui , Shape & shape )
{
   std::deque<Point*> points= shape.getPoints();

   switch ( shape.getId() ) {
   case LINE:     ui.drawLine( points[0]->x , points[0]->y , points[1]->x , points[1]->y );                                   break;
   case BEZIER:   ui.drawBezier( points[0]->x , points[0]->y , points[1]->x , points[1]->y , points[2]->x , points[2]->y );   break;
   case ARC:      ui.drawArc( points[0]->x , points[0]->y , points[1]->x , points[1]->y , points[2]->x , points[2]->y );      break;
   }
}