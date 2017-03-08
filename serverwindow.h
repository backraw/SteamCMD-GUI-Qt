#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QFrame>

#include "servers.h"


namespace Ui {
class ServerWindow;
}

class ServerWindow : public QFrame
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

    void setServer(steamcmd::Server *server);

private:
    Ui::ServerWindow *ui;

private:
    steamcmd::Server *m_server;
};

#endif // SERVERWINDOW_H
