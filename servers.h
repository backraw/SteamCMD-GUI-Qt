#ifndef SERVERS_H
#define SERVERS_H

#include <string>


namespace steamcmd {

struct Server
{
    Server(const bool &steamclient, const bool &steamcmd, const bool &anonymous, const int &appid, const std::string &name)
        : m_steamclient(steamclient)
        , m_steamcmd(steamcmd)
        , m_anonymous(anonymous)
        , m_appid(appid)
        , m_name(name)
    {
    }

    const bool m_steamclient;
    const bool m_steamcmd;
    const bool m_anonymous;
    const int m_appid;
    const std::string m_name;
};

} // namespace steamcmd

#endif // SERVERS_H
