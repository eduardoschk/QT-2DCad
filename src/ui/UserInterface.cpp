#include "UserInterface.h"
#include <QFileDialog>
#include <QString>
#include <QPoint>
#include <QMessageBox>

#include "App.h"
#include "MainWindow.h"
#include "NewDrawPopup.h"

UserInterface::UserInterface(App& _owner,QWidget * parent) : QWidget(parent),app(_owner),mainWindow(*this) {}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::drawTempLine(int xInit,int yInit,int xFinal,int yFinal)
{
   mainWindow.drawTempLine(QPoint(xInit,yInit),QPoint(xFinal,yFinal));
}

void UserInterface::drawTempBezier(int xInit,int yInit,int xControl,int yControl,int xFinal,int yFinal)
{
   mainWindow.drawTempBezier(QPoint(xInit,yInit),QPoint(xControl,yControl),QPoint(xFinal,yFinal));
}

void UserInterface::drawTempArc(int xCenter,int yCenter,int xInit,int yInit,int xFinal,int yFinal)
{
   mainWindow.drawTempArc(QPoint(xCenter,yCenter),QPoint(xInit,yInit),QPoint(xFinal,yFinal));
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::drawLine(int xInit,int yInit,int xFinal,int yFinal)
{
   mainWindow.drawLine(QPoint(xInit,yInit),QPoint(xFinal,yFinal));
}

void UserInterface::drawBezier(int xInit,int yInit,int xControl,int yControl,int xFinal,int yFinal)
{
   mainWindow.drawBezier(QPoint(xInit,yInit),QPoint(xControl,yControl),QPoint(xFinal,yFinal));
}

void UserInterface::drawArc(int xCenter,int yCenter,int xInit,int yInit,int xFinal,int yFinal)
{
   mainWindow.drawArc(QPoint(xCenter,yCenter),QPoint(xInit,yInit),QPoint(xFinal,yFinal));
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::setShapeArc()
{
   app.actionSetShapeArc();
   mainWindow.setShapArc();
}

void UserInterface::setShapeLine()
{
   app.actionSetShapeLine();
   mainWindow.setShapeLine();
}

void UserInterface::setShapeBezier()
{
   app.actionSetShapeBezier();
   mainWindow.setShapeBezier();
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::setDrawingScale(float scale)
{
   mainWindow.setDrawingScale(scale);
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::mouseMoveEventInDrawArea(QPoint point)
{
   app.actionMouseMoveInDrawArea(point.x(), point.y());
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

///////////////////////////////////////////////////////////////////////////////

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

void UserInterface::setTitleWindow(const char* name)
{
   mainWindow.setWindowTitle(name);
}

void UserInterface::createDrawArea(int width,int height)
{
   mainWindow.createNewDrawArea(width,height);
}