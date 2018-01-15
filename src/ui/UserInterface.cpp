#include <vector>

#include <QPoint>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>

#include "UserInterface.h"

#include "App.h"
#include "MainWindow.h"
#include "NewDrawPopup.h"

UserInterface::UserInterface(App& _app) : app(_app),initialized(false),mainWindow(*this) {}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::init()
{ 
   initialized= true; 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::markOffAllOptions() 
{ 
   mainWindow.markOffAllOptions(); 
}

void UserInterface::markArcOptionAsSelected() 
{ 
   mainWindow.markArcOptionAsSelected(); 
}

void UserInterface::markLineOptionAsSelected() 
{ 
   mainWindow.markLineOptionAsSelected(); 
}

void UserInterface::markBezierOptionAsSelected() 
{ 
   mainWindow.markBezierOptionAsSelected(); 
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
   QMessageBox::warning(this,QString::fromLatin1("Atenção"),QString::fromLatin1(message),
      QMessageBox::StandardButton::Ok);
}

bool UserInterface::confirmOperation(std::string _message)
{
   const char* message = _message.c_str();
   QMessageBox::StandardButton response;
   response = QMessageBox::question(this,QString::fromLatin1("Atenção"),QString::fromLatin1(message),
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

void UserInterface::startCreateArc()
{ 
   initialized ? app.startCommandDrawArc() : 0;
}

void UserInterface::startCreateLine()
{ 
   initialized ? app.startCommandDrawLine() : 0;
}

void UserInterface::startCreateBezier()
{ 
   initialized ? app.startCommandDrawBezier() : 0;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::mouseMoveEventInDrawArea(QPoint point) 
{ 
   initialized ? app.actionMouseMoveInDrawArea(Point(point.x(),point.y())) : 0;
}

void UserInterface::mousePressEventInDrawArea(QPoint point) 
{ 
   initialized ? app.actionMousePressInDrawArea(Point(point.x(),point.y())) : 0;
}

void UserInterface::mouseReleaseEventInDrawArea(QPoint point) 
{ 
   initialized ? app.actionMouseReleaseInDrawArea(Point(point.x(),point.y())) : 0;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startOptionNewFile() 
{ 
   initialized ? app.startCommandNewFile() : 0;
}

void UserInterface::startOptionOpenFile()
{ 
   initialized ? app.startCommandOpenFile() : 0;
}

void UserInterface::startOptionSaveFile()
{ 
   initialized ? app.startCommandSaveFile() : 0;
}

void UserInterface::startOptionSaveAsFile()
{ 
   initialized ? app.startCommandSaveAsFile() : 0;
}

void UserInterface::startOptionQuit()
{ 
   initialized ? app.startCommandQuit() : 0;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startResizeWindow(QSize size)
{
   initialized ? app.startCommandResizeWindow(size.width(),size.height()) : 0;
}

void UserInterface::startZoomValueChange(int value)
{ 
   initialized ? app.startCommandZoomValueChange(value) : 0;
}

///////////////////////////////////////////////////////////////////////////////

Size UserInterface::getSizeWindow()
{
   QSize size= mainWindow.getSizeWindow();
   return Size(size.width(),size.height());
}

void UserInterface::setSizeDrawArea(Size size) 
{ 
   mainWindow.setSizeDrawArea(QSize(size.width,size.height)); 
}

void UserInterface::setZoomScaleWidget(int value)
{
   mainWindow.setZoomScaleWidget(value);
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::activateMouseTracking() 
{ 
   mainWindow.activateMouseTracking(); 
}

void UserInterface::disableMouseTracking() 
{ 
   mainWindow.disableMouseTracking(); 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::setTitleWindow(const char* name) 
{ 
   mainWindow.setWindowTitle(name); 
}

void UserInterface::createDrawArea(Size size) 
{ 
   mainWindow.createNewDrawArea(QSize(size.width,size.height)); 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::clearArea() 
{ 
   mainWindow.clearArea(); 
}

void UserInterface::eraseShape(int idShape) 
{ 
   mainWindow.eraseShape(idShape); 
}

void UserInterface::drawPoint(int idShape,Point point) 
{ 
   mainWindow.drawPoint(idShape,QPoint(point.x,point.y)); 
}

void UserInterface::drawPoints(int idShape,std::deque<Point> points)
{
   std::vector<QPoint> qPoints;
   for (Point point : points) {
      qPoints.push_back(QPoint(point.x,point.y));
   }
   mainWindow.drawPoints(idShape,qPoints);
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::createVerticalScrollBar(int pageStep,int limit)
{
   mainWindow.createVerticalScrollBar(pageStep,limit);
}

void UserInterface::createHorizontalScrollBar(int pageStep,int limit)
{
   mainWindow.createHorizontalScrollBar(pageStep,limit);
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::verticalScrollMove(int value)
{
   initialized ? app.startMoveYScroll(value) : 0;
}

void UserInterface::horizontalScrollMove(int value)
{
   initialized ? app.startMoveXScroll(value) : 0;
}
