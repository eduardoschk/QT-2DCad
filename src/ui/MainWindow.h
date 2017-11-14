#pragma once
#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <QMainWindow>
#include <string>

class DrawArea;
class QSlider;
class QLabel;
class UserInterface;

class MainWindow 
    : public QMainWindow
{
    Q_OBJECT
private:
    UserInterface * owner;
    DrawArea * drawArea;
    QSlider * sliderZoom;

    QAction * line;
    QAction * bezier;
    QAction * arc;

    void configureMenuBar(QMenuBar & menuBar);
    void configureToolBarShapes();
    void configureZoomControlOnStatusBar();
    void resizeEvent( QResizeEvent *event ) override;

public:
    MainWindow( UserInterface * _owner, QWidget * parent = 0);

    void createNewDrawArea( int _width , int _heigth );

public slots:
    void setShapeLine();
    void setShapeBezier();
    void setShapArc();

    void minusZoomClicked();
    void plusZoomClicked();
    void zoomValueChange(int value);
};

#endif // INCLUDED_MAIN_WINDOW_H