#ifndef SERVERLIST_H
#define SERVERLIST_H

#include "servers.h"

#include <vector>


namespace steamcmd {

class ServerList : public std::vector<Server>
{
public:
    ServerList();

    void parse();
    void update();
};

} // namespace steamcmd

#endif // SERVERLIST_H
