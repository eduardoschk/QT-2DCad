#include "CommandOpen.h"
#include "Data.h"
#include "UserInterface.h"
#include "Archive.h"
#include "Shape.h"
#include "Point.h"

void CommandOpen::exec( Data& data , UserInterface& ui )
{
    Archive * archive = new Archive();
    archive= archive->open( pathAndFileName );
    ui.createDrawArea( archive->getWidth(), archive->getHeight() );

    std::deque<Shape*> shapes= archive->getShapes();
    for ( int i= 0 ; i < shapes.size() ; ++i ) {
        std::deque<Point*> points= shapes[i]->getPoints();

        switch ( shapes[i]->getId() ) {
        case LINE:      ui.drawLine( points[0]->x , points[0]->y , points[1]->x , points[1]->y );                                   break;
        case BEZIER:    ui.drawBezier( points[0]->x , points[0]->y , points[1]->x , points[1]->y , points[2]->x , points[2]->y );   break;
        case ARC:       ui.drawArc( points[0]->x , points[0]->y , points[1]->x , points[1]->y , points[2]->x , points[2]->y );      break;
        break;
        }
    }

}