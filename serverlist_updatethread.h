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
    ServerList *m_serverlist;
    QLabel *m_label_status;
};

} // namespace steamcmd

#endif // SERVERLISTUPDATETHREAD_H
