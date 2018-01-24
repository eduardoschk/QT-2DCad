#include "CommandOpenFile.h"
#include "Data.h"
#include "File.h"
#include "Shape.h"
#include "Coordinate.h"
#include "ZoomControl.h"
#include "UserInterface.h"

void CommandOpenFile::exec(Data& data,UserInterface& ui)
{
   bool response= true;

   if (data.hasFile() && !data.getCurrentFile().isSaved())
      response= ui.confirmOperation("There are a file open and your changes isn't save, do you want to continue?");

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
   ui.createDrawArea();
   ui.setZoomScaleWidget(ZOOM::DEFAULT);
   ui.setTipMessage("Select the shape");
   std::deque<Shape*> shapes= opennedFile.getShapes();
   for (Shape* shape : shapes)
      drawShape(ui,*shape,opennedFile.getDataViewController());
}

void CommandOpenFile::drawShape(UserInterface& ui,Shape& shape,DataViewController& dataViewController)
{
   ui.markOffAllOptions();
   ui.drawCoordinates(shape.getId(),shape.getCoordinatesToDraw(dataViewController));
}