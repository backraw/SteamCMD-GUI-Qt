#ifndef SERVERLISTUPDATETHREAD_H
#define SERVERLISTUPDATETHREAD_H

#include <QLabel>
#include <QObject>

#include "serverlist.h"


namespace steamcmd {

class ServerListUpdateThread : public QObject
{
    Q_OBJECT

public:
    ServerListUpdateThread(ServerList *serverlist, QLabel *label_status);

public slots:
    void run();

signals:
    void finished();

private:
    QLabel *m_label_status;
    ServerList *m_serverlist;
};

} // namespace steamcmd

#endif // SERVERLISTUPDATETHREAD_H
