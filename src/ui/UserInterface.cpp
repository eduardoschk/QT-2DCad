#include <QPoint>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>

#include "App.h"
#include "MainWindow.h"
#include "NewDrawPopup.h"
#include "UserInterface.h"

std::string UserInterface::requestPathFileToSave(std::string fileName)
{
   const char* a = fileName.c_str();
   QString path = QFileDialog::getSaveFileName(this,tr("Salvar"),
      a,
      tr("Custom(.cad);"));

   return path.toStdString();
}

std::string UserInterface::requestPathFileToOpen()
{
   QString path = QFileDialog::getOpenFileName(this);

   return path.toStdString();
}

void UserInterface::showErrorMessage(std::string _message)
{
   const char* message = _message.c_str();
   QMessageBox::warning(this,tr("Atenção"),message,
      QMessageBox::StandardButton::Ok);
}

bool UserInterface::confirmOperation(std::string _message)
{
   const char* message = _message.c_str();
   QMessageBox::StandardButton response;
   response = QMessageBox::question(this,tr("Atenção"),message,
      QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);

   return (response == QMessageBox::Yes) ? true : false ;
}

NEW_FILE_STRUCTURE UserInterface::showPopupNewFile()
{
   NEW_FILE_STRUCTURE nfs;
   
   NewDrawPopup ndp(&nfs);
   ndp.exec();
   
   return nfs;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::optionShapeArc() 
{ 
   app.actionDrawArc(); 
}

void UserInterface::optionShapeLine() 
{ 
   app.actionDrawLine(); 
}

void UserInterface::optionShapeBezier() 
{ 
   app.actionDrawBezier(); 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::mouseMoveEventInDrawArea(QPoint point) 
{ 
   app.actionMouseMoveInDrawArea(point.x(),point.y()); 
}

void UserInterface::mousePressEventInDrawArea(QPoint point) 
{ 
   app.actionMousePressInDrawArea(point.x(),point.y());
}

void UserInterface::mouseReleaseEventInDrawArea(QPoint point) 
{ 
   app.actionMouseReleaseInDrawArea(point.x(),point.y()); 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::optionNewFile() 
{ 
   app.actionNewFile(); 
}

void UserInterface::optionOpenFile()
{ 
   app.actionOpenFile(); 
}

void UserInterface::optionSaveFile()
{ 
   app.actionSaveFile(); 
}

void UserInterface::optionSaveAsFile() 
{ 
   app.actionSaveAsFile(); 
}

void UserInterface::optionQuit() 
{ 
   app.actionQuit(); 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::zoomValueChange(int value) 
{ 
   app.actionZoomValueChange(value); 
}
