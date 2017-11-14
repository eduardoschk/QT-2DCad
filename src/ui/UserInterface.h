#pragma once
#ifndef INCLUDED_USER_INTERFACE_H
#define INCLUDED_USER_INTERFACE_H

#include <QWidget>

class MainWindow;
class NewDrawPopup;
class App;

class UserInterface 
    : public QWidget
{
    Q_OBJECT
private:
    MainWindow * mainWindow;
    NewDrawPopup * newDrawPopup;
    App * owner;

public:
    UserInterface( App * _owner, QWidget * parent = 0 );
    ~UserInterface();
    
    void setTitleWindow( const char* name );
    void createDrawArea( int width , int height );

public slots:
    void optionNewFile();
    void optionOpenFile();
    void optionSaveFile();
    void optionSaveAsFile();

    void createFile( QString name , int width , int height );
};

#endif // INCLUDED_USER_INTERFACE_H