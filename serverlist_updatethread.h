#ifndef SERVERLISTUPDATETHREAD_H
#define SERVERLISTUPDATETHREAD_H

#include <QLabel>
#include <QObject>

#include "serverlist.h"


namespace steamcmd {

class ServerList_UpdateThread : public QObject
{
    Q_OBJECT

public:
    ServerList_UpdateThread(ServerList *serverlist, QLabel *label_status);

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
