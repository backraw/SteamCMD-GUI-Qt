#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vector>

#include "settings.h"
#include "servers.h"


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

private:
    void parse_serverlist();

private:
    Ui::MainWindow *ui;

    std::vector<steamcmd::Server> m_serverlist;
    steamcmd::Settings m_settings;
};

#endif // MAINWINDOW_H
