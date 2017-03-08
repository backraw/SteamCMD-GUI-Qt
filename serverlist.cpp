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

const Server &ServerList::from_name(const std::__cxx11::string &name)
{
    auto it = begin();

    while (it->m_name != name && it != end())
    {
        ++it;
    }

    return *it;
}

} // namespace steamcmd
