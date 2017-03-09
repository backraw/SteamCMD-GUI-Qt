#include "serverlist_updatethread.h"


namespace steamcmd {

ServerListUpdateThread::ServerListUpdateThread(ServerList *serverlist, QLabel *label_status)
    : m_serverlist(serverlist)
    , m_label_status(label_status)
{
}

void ServerListUpdateThread::run()
{
    // Set status
    m_label_status->setText("Status: Parsing remote Dedicated Server List...");

    // Update the server list vector
    m_serverlist->update();

    // emit signal finished()
    emit finished();
}

} // namespace steamcmd
