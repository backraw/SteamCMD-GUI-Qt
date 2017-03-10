#ifndef SERVERLIST_H
#define SERVERLIST_H

#include "servers.h"

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

} // namespace steamcmd

#endif // SERVERLIST_H
