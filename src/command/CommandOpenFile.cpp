#include "CommandOpenFile.h"
#include "Data.h"
#include "File.h"
#include "Shape.h"
#include "Point.h"
#include "ZoomControl.h"
#include "UserInterface.h"

void CommandOpenFile::exec(Data& data,UserInterface& ui)
{
   bool response= true;

   if (data.hasFile() && !data.getCurrentFile().isSaved())
      response= ui.confirmOperation("O arquivo aberto não está com suas atualizações salvas, deseja continuar?");

   if (response) {
      std::string completedPath= ui.requestPathFileToOpen();

      if (completedPath.size() > 0) {
         File* file= data.open(completedPath);
         file->getDataViewController().setWindowSize(ui.getSizeWindow());

         FileParams params= dividerNameOfPath(completedPath);
         file->setPath(params.path);
         file->setFileName(params.name);

         data.setCurrentFile(file);
         drawOpenFile(ui,*file);
      }
   }
}

void CommandOpenFile::drawOpenFile(UserInterface& ui,File& opennedFile)
{
   ui.setZoomScaleWidget(ZOOM::DEFAULT);
   ui.createDrawArea();
   std::deque<Shape*> shapes= opennedFile.getShapes();
   for (Shape* shape : shapes)
      drawShape(ui,*shape,opennedFile.getDataViewController());
}

void CommandOpenFile::drawShape(UserInterface& ui,Shape& shape,DataViewController& dataViewController)
{
   ui.markOffAllOptions();
   ui.drawPoints(shape.getId(),shape.getPointsToDraw(dataViewController));
}