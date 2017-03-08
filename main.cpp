#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Show the main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Run the main loop
    return a.exec();
}
