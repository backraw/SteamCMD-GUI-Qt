#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QModelIndex>

#include "serverwindow.h"

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

    void on_listWidgetServerList_doubleClicked(const QModelIndex &index);

private:
    void populate_serverlist_widget();

private:
    Ui::MainWindow *ui;
    QLabel m_label_status;
    ServerWindow m_server_window;

private:
    steamcmd::ServerList m_serverlist;
    steamcmd::Settings m_settings;
};

#endif // MAINWINDOW_H
