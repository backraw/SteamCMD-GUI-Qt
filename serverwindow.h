#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QFrame>

#include "servers.h"
#include "settings.h"


namespace Ui {
class ServerWindow;
}

class ServerWindow : public QFrame
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

    void setServer(const steamcmd::Server * const server, const steamcmd::Settings *settings);

private slots:
    void on_pushButtonLocalInstallationsBrowse_clicked();

private:
    Ui::ServerWindow *ui;

private:
    const steamcmd::Settings *m_settings;
    const steamcmd::Server *m_server;
};

#endif // SERVERWINDOW_H
