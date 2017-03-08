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

    void setServer(const steamcmd::Server * const server);

private:
    Ui::ServerWindow *ui;

private:
    const steamcmd::Server *m_server;
};

#endif // SERVERWINDOW_H
