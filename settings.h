#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "jsonparser.h"


namespace steamcmd {

class Settings : public JsonParser
{
public:
    Settings();

    const std::string findSteamCMD(const std::string executable = "steamcmd", const int tries = 0);
};

} // namespace steamcmd

#endif // SETTINGS_H
