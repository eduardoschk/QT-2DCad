#include "UserInterface.h"
#include <QFileDialog>
#include <QString>
#include <QPoint>
#include <QMessageBox>

#include "MainWindow.h"
#include "NewDrawPopup.h"
#include "App.h"

UserInterface::UserInterface( App * _owner , QWidget * parent) : 
   QWidget( parent ), owner( _owner ), newDrawPopup( nullptr )
{
    mainWindow= new MainWindow(this);
}

UserInterface::~UserInterface() 
{
   if ( newDrawPopup )
      delete newDrawPopup;
   delete mainWindow;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::drawLine( int xInit , int yInit , int xFinal , int yFinal )
{
   mainWindow->drawLine(QPoint( xInit, yInit ), QPoint( xFinal , yFinal));
}

void UserInterface::drawBezier( int xInit , int yInit , int xControl , int yControl , int xFinal , int yFinal )
{
   mainWindow->drawBezier( QPoint( xInit , yInit ) , QPoint( xControl , yControl ) , QPoint(xFinal, yFinal) );
}

void UserInterface::drawArc( int xCenter , int yCenter , int xInit , int yInit , int xFinal , int yFinal )
{
   mainWindow->drawArc( QPoint( xCenter , yCenter ) , QPoint( xInit , yInit ) , QPoint( xFinal , yFinal ) );
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::drawLineFinish( QPoint initial , QPoint final )
{
   owner->actionDrawLine( initial.x() , initial.y() , final.x() , final.y() );
}

void UserInterface::drawBezierFinish( QPoint initial , QPoint control , QPoint final )
{
   owner->actionDrawBezier( initial.x() , initial.y() , control.x() , control.y() , final.x() , final.y() );
}

void UserInterface::drawArcFinish( QPoint center , QPoint initial , QPoint final )
{
   owner->actionDrawArc( center.x() , center.y() , initial.x() , initial.y() , final.x() , final.y() );
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::optionNewFile()
{
   owner->actionNewFile();
}

void UserInterface::optionOpenFile()
{
   owner->actionOpenFile();
}

void UserInterface::optionSaveFile() 
{
   owner->actionSaveFile();
}

void UserInterface::optionSaveAsFile()
{
   owner->actionSaveAsFile();
}

void UserInterface::optionQuit()
{
    owner->actionQuit();
}

///////////////////////////////////////////////////////////////////////////////

std::string UserInterface::requestPathFileToSave(std::string fileName)
{
   const char* a = fileName.c_str();
   QString path = QFileDialog::getSaveFileName( this , tr( "Salvar" ) ,
      a ,
      tr( "Custom(.cad);;Images (*.png *.xpm *.jpg)"));
    
   return path.toStdString();
}

std::string UserInterface::requestPathFileToOpen()
{
   QString path = QFileDialog::getOpenFileName( this );

   return path.toStdString();
}

void UserInterface::showErrorMessage( std::string _message )
{
   const char* message = _message.c_str();
   QMessageBox::warning( this , tr( "Atenção" ) , message ,
      QMessageBox::StandardButton::Ok );
}

bool UserInterface::confirmOperation( std::string _message )
{
   const char* message = _message.c_str();
   QMessageBox::StandardButton response;
   response = QMessageBox::question( this , tr("Atenção") , message ,
      QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No );

   return ( response == QMessageBox::Yes ) ? true : false ;
}

void UserInterface::showPopupNewFile()
{
   newDrawPopup = new NewDrawPopup();
   connect( newDrawPopup , SIGNAL( createNewArchive( QString , int , int ) ) , this , SLOT( createFile( QString , int , int ) ) );
   connect( newDrawPopup , SIGNAL( sigCancel() ) , this , SLOT( cancelCreateFile() ) );
   newDrawPopup->show();
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::setTitleWindow( const char* name )
{
    mainWindow->setWindowTitle( name );
}

void UserInterface::createDrawArea( int width , int height )
{
    mainWindow->createNewDrawArea( width , height );
}

void UserInterface::cancelCreateFile()
{
   delete newDrawPopup;
   newDrawPopup= nullptr;
}

void UserInterface::createFile( QString name , int _width , int _height )
{
   if ( newDrawPopup ) {
      delete newDrawPopup;
      newDrawPopup= nullptr;
   }
   owner->actionCreateArhive( name.toStdString() , _width , _height );
}