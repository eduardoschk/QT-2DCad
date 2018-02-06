#include "CommandOpenFile.h"
#include "Data.h"
#include "File.h"
#include "Shape.h"
#include "Coordinate.h"
#include "ZoomControl.h"
#include "UserInterface.h"

bool CommandOpenFile::checkIfCanCreateFile(Data& data,UserInterface& ui)
{
   bool response= true;
   if (data.hasFile() && !data.getCurrentFile().isSaved())
      response= ui.confirmOperation("There's a file open and it's not save, do you want to continue?");
   return response;
}

///////////////////////////////////////////////////////////////////////////////

void CommandOpenFile::drawOpenFile(UserInterface& ui,File& opennedFile)
{
   ui.createDrawArea();
   ui.markOffAllOptions();
   ui.setZoomScaleWidget(ZOOM::DEFAULT);
   ui.setTipMessage("Select the shape");
   ui.setTitleWindow(opennedFile.getFileName().c_str());

   std::deque<Shape*> shapes= opennedFile.getShapes();
   for (Shape* shape : shapes)
      ui.drawCoordinates(shape->getId(),shape->getCoordinatesToDraw(opennedFile.getDataViewController()));
}

///////////////////////////////////////////////////////////////////////////////

void CommandOpenFile::exec(Data& data,UserInterface& ui)
{
   if (checkIfCanCreateFile(data,ui)) {
      std::string completedPath= ui.requestPathFileToOpen();

      if (completedPath.size() > 0) {
         File* file= data.open(completedPath);
         file->getDataViewController().setWindowSize(ui.getSizeWindow());

         FileParams& params= getNameAndFolderPathOfAbsolutePath(completedPath);
         file->setPath(params.path);
         file->setFileName(params.name);

         data.setCurrentFile(file);
         drawOpenFile(ui,*file);
      }
   }
}
