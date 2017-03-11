#ifndef SERVERLIST_H
#define SERVERLIST_H

#include "servers.h"

#include <QLabel>
#include <QObject>

#include <string>
#include <vector>


namespace steamcmd {

class ServerList : public std::vector<Server>
{
public:
    ServerList();

    void parse();
    void update();

    Server &fromName(const std::string &name);
};

class ServerList_UpdateThread : public QObject
{
    Q_OBJECT

public:
    ServerList_UpdateThread(ServerList *serverlist, QLabel *label_status, QObject *parent = 0);

public slots:
    void run();

signals:
    void finished();

private:
    ServerList *m_serverlist;
    QLabel *m_label_status;
};

} // namespace steamcmd

#endif // SERVERLIST_H
