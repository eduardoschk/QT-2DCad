#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <QMainWindow>
#include <string>

class DrawArea;
class QSlider;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private:
    DrawArea * drawArea;
    QSlider * sliderZoom;

public slots:
    void minusZoomClicked();
    void plusZoomClicked();
    void zoomValueChange(int value);

    void optionNewArchive();
    //void optionOpenArchive();
    //void optionSaveArchive();
    //void optionSaveAsArchive();

    void createNewArchive( QString name, int width, int height);
};

#endif // INCLUDED_MAIN_WINDOW_H