#include "jsonparser.h"
#include "paths.h"
#include "serverlist.h"

#include <QProcess>


namespace steamcmd {

ServerList::ServerList()
    : std::vector<Server>()
{
    // Parse https://developer.valvesoftware.com/wiki/Dedicated_Servers_List
    // if ~/.config/steamcmd-gui-qt/serverlist.json does not exist
    if (!PATH_SERVERLIST_JSON.exists())
    {
        update();
    }

    parse();
}

void ServerList::parse()
{
    // Clear this vector
    clear();

    // Parse ~/.config/steamcmd-gui-qt/serverlist.json
    JsonParser serverlist(PATH_SERVERLIST_JSON.fileName().toStdString());

    for (auto it = serverlist.begin(); it != serverlist.end(); ++it)
    {
        // Get server details
        nlohmann::json details = it.value();

        // Add the deserialized server item to the vector of servers
        push_back(steamcmd::Server(details["steamclient"].get<bool>(), details["steamcmd"].get<bool>(), details["anonymous"].get<bool>(), details["appid"].get<int>(), it.key()));
    }
}

void ServerList::update()
{
    // Parse https://developer.valvesoftware.com/wiki/Dedicated_Servers_List
    QProcess serverlist_py;
    serverlist_py.start("python3 ./serverlist.py");
    serverlist_py.waitForFinished();

    // Parse ~/.config/steamcmd-gui-qt/serverlist.json
    parse();
}

Server &ServerList::fromName(const std::__cxx11::string &name)
{
    // Loop through each item in this vector and compare its 'm_name'
    // member to 'name'
    auto it = begin();
    while (it->m_name != name && it != end())
    {
        ++it;
    }

    // Return the found Server instance
    return *it;
}


ServerList_UpdateThread::ServerList_UpdateThread(ServerList *serverlist, QLabel *label_status, QObject *parent)
    : Thread(parent)
    , m_serverlist(serverlist)
    , m_label_status(label_status)
{
}

void ServerList_UpdateThread::start(const QObject *receiver, const char *slot)
{
    startWithSignal(SIGNAL(finished()), receiver, slot);
}

void ServerList_UpdateThread::run()
{
    // Set status
    m_label_status->setText("Status: Parsing remote Dedicated Server List...");

    // Update the server list vector
    m_serverlist->update();

    // emit signal finished()
    emit finished();
}

} // namespace steamcmd
