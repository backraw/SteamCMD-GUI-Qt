#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "jsonparser.h"


namespace steamcmd {

/**
 * @brief steamcmd::Settings
 *
 * Inherits from steamcmd::JsonParser and extends it with
 * a method to find the SteamCMD executable using the 'which' command.
 */
class Settings : public JsonParser
{
public:
    /**
     * @brief c'tor
     *
     * Call steamcmd::JsonParser(<path to ~/.config/steamcmd-gui-qt/settings.json>)
     */
    Settings();

    /**
     * @brief Find and return the path to the SteamCMD executable using 'which'
     *
     * @param executable The executable to find
     * @param tries The amount of times we have tried to find \<executable\>
     *
     * @return The path to the executable - an empty string if nothing has been found
     */
    const std::string findSteamCMD(const std::string executable = "steamcmd", const int tries = 0);
};

} // namespace steamcmd

#endif // SETTINGS_H
