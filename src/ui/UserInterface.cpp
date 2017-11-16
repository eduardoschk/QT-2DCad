#include "UserInterface.h"
#include <QFileDialog>
#include <QString>
#include <string>
#include <QPoint>

#include "MainWindow.h"
#include "NewDrawPopup.h"
#include <iostream>
#include "App.h"

UserInterface::UserInterface( App * _owner , QWidget * parent) : QWidget( parent ), owner(_owner)
{
    mainWindow= new MainWindow(this);
}

UserInterface::~UserInterface() {}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::drawLine( int x1 , int y1 , int x2 , int y2 )
{
    mainWindow->drawLine(QPoint( x1, y1 ), QPoint( x2 , y2));
}

void UserInterface::drawBezier( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 )
{
    mainWindow->drawBezier( QPoint( x1 , y1 ) , QPoint( x2 , y2 ) , QPoint(x3, y3) );
}

void UserInterface::drawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 )
{
    mainWindow->drawArc( QPoint( x1 , y1 ) , QPoint( x2 , y2 ) , QPoint( x3 , y3 ) );
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
    newDrawPopup = new NewDrawPopup();
    connect( newDrawPopup , SIGNAL( createNewArchive( QString , int , int ) ) , this , SLOT( createFile( QString , int , int ) ) );
    newDrawPopup->show();
}

void UserInterface::optionOpenFile()
{
    QFileDialog dialog( this );

    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setAcceptMode( QFileDialog::AcceptOpen );
    QString file = QFileDialog::getOpenFileName(this);

    owner->actionOpenFile( file.toStdString() );
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
        tr( "Custom(.tois);;Images (*.png *.xpm *.jpg)"));
    
    return path.toStdString();
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

void UserInterface::createFile( QString name , int _width , int _height )
{
    owner->actionNewFile( name.toStdString() , _width , _height );
}