#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settings.h"
#include "serverlist.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonSteamCMDExecutableBrowse_clicked();

    void on_lineEditSteamCMDExecutablePath_textChanged(const QString &text);

    void on_pushButtonServerListUpdate_clicked();

private:
    void populate_serverlist_widget();

private:
    Ui::MainWindow *ui;

    steamcmd::ServerList m_serverlist;
    steamcmd::Settings m_settings;
};

#endif // MAINWINDOW_H
