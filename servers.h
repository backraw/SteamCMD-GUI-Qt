#ifndef SERVERS_H
#define SERVERS_H

#include <string>


namespace steamcmd {

/**
 * @brief steamcmd::Server
 *
 * Structure holding meta information about a dedicated server.
 * This is used to "serialize" the ~/.config/steamcmd-gui-qt/serverlist.json file.
 */
struct Server
{
    /**
     * @brief c'tor
     *
     * @param steamclient   A boolean value holding true if a Steam client is required to install this server
     * @param steamcmd      A boolean value holding true if SteamCMD is required to install this server
     * @param anonymous     A boolean value holding true if no Steam logon is required to install this server
     * @param appid         An integer value holding the AppID number of the server
     * @param name          A string value holding the name of the server
     */
    Server(const bool &steamclient, const bool &steamcmd, const bool &anonymous, const int &appid, const std::string &name)
        : m_steamclient(steamclient)
        , m_steamcmd(steamcmd)
        , m_anonymous(anonymous)
        , m_appid(appid)
        , m_name(name)
    {
    }

    const bool m_steamclient;   ///< A boolean value holding true if a Steam client is required to install this server
    const bool m_steamcmd;      ///< A boolean value holding true if SteamCMD is required to install this server
    const bool m_anonymous;     ///< A boolean value holding true if no Steam logon is required to install this server
    const int m_appid;          ///< An integer value holding the AppID number of the server
    const std::string m_name;   ///< A string value holding the name of the server
};

} // namespace steamcmd

#endif // SERVERS_H
