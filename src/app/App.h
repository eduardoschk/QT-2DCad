#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <QApplication>

class MainWindow;

class App :
    public QApplication
{
private:
    MainWindow * window;
public:
    ~App();
    App(int argc, char **argv);

    void run();
};

#endif // INCLUDED_APP_H