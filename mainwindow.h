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

/**
 * @brief window/MainWindow: The main window of the program.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief c'tor
     *
     * @param parent The parent widget of this window (always 0)
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // GroupBox: SteamCMD Executable
    void on_pushButtonSteamCMDExecutableBrowse_clicked();
    void on_lineEditSteamCMDExecutablePath_textChanged(const QString &text);
    void on_pushButtonSteamCMDExecutableFind_clicked();

    // GroupBox: Server List
    void on_pushButtonServerListUpdate_clicked();
    void on_listWidgetServerList_doubleClicked(const QModelIndex &index);

    // Others
    void on_serverlist_updatethread_finished();
    void on_server_window_closed();

private:
    void populateServerlistWidget();

private:
    Ui::MainWindow *ui;
    QLabel m_label_status;
    ServerWindow m_server_window;

private:
    steamcmd::ServerList m_serverlist;
    steamcmd::Settings m_settings;
};

#endif // MAINWINDOW_H
