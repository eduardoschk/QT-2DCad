#include "CommandOpen.h"
#include "Data.h"
#include "UserInterface.h"
#include "File.h"
#include "Shape.h"
#include "Point.h"

void CommandOpen::exec(Data& data,UserInterface& ui)
{
   bool response= true;
   if (data.hasFile() && !data.getCurrentFile().isSaved())
      response= ui.confirmOperation("O arquivo aberto não está com suas atualizações salvas, deseja continuar?");

   if (response) {
      std::string completedPath= ui.requestPathFileToOpen();

      if (completedPath.size() > 0) {
         File* file= data.open(completedPath);

         FileParams params= dividerNameOfPath(completedPath);
         file->setPath(params.path);
         file->setFileName(params.name);

         data.setCurrentFile(file);

         ui.createDrawArea(file->getWidth(),file->getHeight());

         std::deque<Shape*> shapes= file->getShapes();
         for (int i= 0 ; i < shapes.size() ; ++i)
            drawShape(ui,*shapes[i]);
      }
   }
}

void CommandOpen::drawShape(UserInterface& ui,Shape& shape)
{
   std::deque<Point*> points= shape.getPoints();

   switch (shape.getId()) {
      case SHAPE_ID::LINE:     ui.drawLine(points[0]->x,points[0]->y,points[1]->x,points[1]->y);                               break;
      case SHAPE_ID::BEZIER:   ui.drawBezier(points[0]->x,points[0]->y,points[1]->x,points[1]->y,points[2]->x,points[2]->y);   break;
      case SHAPE_ID::ARC:      ui.drawArc(points[0]->x,points[0]->y,points[1]->x,points[1]->y,points[2]->x,points[2]->y);      break;
   }
}