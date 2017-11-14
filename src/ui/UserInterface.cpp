#include "UserInterface.h"
#include <QFileDialog>
#include <QString>
#include <string>

#include "MainWindow.h"
#include "NewDrawPopup.h"
#include <iostream>
#include "App.h"

UserInterface::UserInterface( App * _owner , QWidget * parent) : QWidget( parent ), owner(_owner)
{
    mainWindow= new MainWindow(this);
}

UserInterface::~UserInterface() {}

void UserInterface::optionOpenFile()
{
    QFileDialog dialog( this );

    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setAcceptMode( QFileDialog::AcceptOpen );
    QString file = QFileDialog::getOpenFileName(this);

    owner->actionOpenFile( file.toStdString() );
}

void UserInterface::optionSaveFile() {}

void UserInterface::optionSaveAsFile()
{
    QFileDialog dialog( this );
    dialog.setFileMode( QFileDialog::AnyFile );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setAcceptMode( QFileDialog::AcceptSave );
    QFileDialog::getOpenFileName( this );
}

void UserInterface::optionNewFile()
{
    newDrawPopup = new NewDrawPopup();
    connect( newDrawPopup , SIGNAL( createNewArchive( QString , int , int ) ) , this , SLOT( createFile( QString , int , int ) ) );
    newDrawPopup->show();
}

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