#include "App.h"
#include "MainWindow.h"

App::App(int argc, char **argv) :QApplication(argc, argv)
{
    window = new MainWindow();

}

App::~App() {}

void App::run()
{
    window->show();
    exec();
}