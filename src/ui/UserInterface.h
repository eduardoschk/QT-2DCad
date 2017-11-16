#pragma once
#ifndef INCLUDED_USER_INTERFACE_H
#define INCLUDED_USER_INTERFACE_H

#include <QWidget>
#include <string>

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

    void drawLine( int x1 , int y1 , int x2 , int y2 );
    void drawBezier( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );
    void drawArc( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 );

    std::string requestPathFileToSave( std::string fileName );

public slots:
    void drawLineFinish(QPoint initial, QPoint final);
    void drawBezierFinish( QPoint initial , QPoint control, QPoint final );
    void drawArcFinish( QPoint center, QPoint initial , QPoint final );

    void optionNewFile();
    void optionOpenFile();
    void optionSaveFile();
    void optionSaveAsFile();
    void optionQuit();

    void createFile( QString name , int width , int height );
};

#endif // INCLUDED_USER_INTERFACE_H