#include <vector>

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include "UserInterface.h"

#include "App.h"
#include "MainWindow.h"

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

std::string UserInterface::showPopupNewFile()
{
   std::string name= QInputDialog::getText(this,tr("Nome"),tr("Digite o nome desejado para o arquivo")).toStdString();
   
   return name;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startCreateArc()
{ 
   if (initialized)
      app.startCommandDrawArc();
}

void UserInterface::startCreateLine()
{ 
   if (initialized)
      app.startCommandDrawLine();
}

void UserInterface::startCreateBezier()
{ 
   if (initialized)
      app.startCommandDrawBezier();
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::mouseMoveEventInDrawArea(Point point) 
{ 
   if (initialized)
      app.actionMouseMoveInDrawArea(point);
}

void UserInterface::mousePressEventInDrawArea(Point point) 
{ 
   if (initialized)
      app.actionMousePressInDrawArea(point);
}

void UserInterface::mouseReleaseEventInDrawArea(Point point) 
{ 
   if (initialized)
      app.actionMouseReleaseInDrawArea(point);
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startOptionNewFile() 
{ 
   if (initialized)
      app.startCommandNewFile();
}

void UserInterface::startOptionOpenFile()
{ 
   if (initialized)
      app.startCommandOpenFile();
}

void UserInterface::startOptionSaveFile()
{ 
   if (initialized)
      app.startCommandSaveFile();
}

void UserInterface::startOptionSaveAsFile()
{ 
   if (initialized)
      app.startCommandSaveAsFile();
}

void UserInterface::startOptionQuit()
{ 
   if (initialized)
      app.startCommandQuit();
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startResizeWindow(Size& size)
{
   if (initialized)
      app.startCommandResizeWindow(size);
}

void UserInterface::startZoomValueChange(int value)
{ 
   if (initialized)
      app.startCommandZoomValueChange(value);
}

///////////////////////////////////////////////////////////////////////////////

Size UserInterface::getSizeWindow()
{
   QSize size= mainWindow.getSizeWindow();
   return Size(size.width(),size.height());
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

void UserInterface::createDrawArea() 
{ 
   mainWindow.createNewDrawArea(); 
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
   mainWindow.drawPoint(idShape,point); 
}

void UserInterface::drawPoints(int idShape,std::deque<Point>& points)
{
   mainWindow.drawPoints(idShape,points);
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::destructVerticalScrollBar()
{
   mainWindow.destructVerticalScrollBar();
}

void UserInterface::destructHorizontalScrollBar()
{
   mainWindow.destructHorizontalScrollBar();
}

void UserInterface::setVerticalScrollBarPosition(int value)
{
   mainWindow.setVerticalScrollBarPosition(value);
}

void UserInterface::setHorizontalScrollBarPosition(int value)
{
   mainWindow.setHorizontalScrollBarPosition(value);
}

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
   if (initialized)
      app.startMoveYScroll(value);
}

void UserInterface::horizontalScrollMove(int value)
{
   if (initialized)
      app.startMoveXScroll(value);
}
