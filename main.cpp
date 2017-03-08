#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

#include "paths.h"


int main(int argc, char *argv[])
{
    // Create directory ~/.config/steamcmd-gui-qt if necessary
    if (!steamcmd::PATH_SETTINGS.exists())
    {
        steamcmd::PATH_CONFIG.mkdir(steamcmd::PATH_SETTINGS.dirName());
    }

    // Parse https://developer.valvesoftware.com/wiki/Dedicated_Servers_List if necessary
    if (!steamcmd::PATH_SERVERLIST_JSON.exists())
    {
        QProcess serverlist;

        serverlist.start("python3 ./serverlist.py");
        serverlist.waitForFinished();
    }

    // Show the main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Run the main loop
    return a.exec();
}
