#include "serverlist_updatethread.h"


namespace steamcmd {

ServerListUpdateThread::ServerListUpdateThread(ServerList *serverlist, QLabel *label_status)
    : m_serverlist(serverlist)
    , m_label_status(label_status)
{
}

void ServerListUpdateThread::run()
{
    m_label_status->setText("Status: Parsing remote Dedicated Server List...");
    m_serverlist->update();

    emit finished();
}

} // namespace steamcmd
