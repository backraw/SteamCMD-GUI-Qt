#include "mainwindow.h"
#include <QApplication>

#include "paths.h"


int main(int argc, char *argv[])
{
    // Create directory ~/.config/steamcmd-gui-qt if necessary
    if (!steamcmd::PATH_SETTINGS.exists())
    {
        steamcmd::PATH_CONFIG.mkdir(steamcmd::PATH_SETTINGS.dirName());
    }

    // Show the main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Run the main loop
    return a.exec();
}
