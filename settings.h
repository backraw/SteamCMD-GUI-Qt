#ifndef SETTINGS_H
#define SETTINGS_H

#include "jsonparser.h"


namespace steamcmd {

class Settings : public JsonParser
{
public:
    Settings();

private:
    void find_steamcmd();
};

} // namespace steamcmd

#endif // SETTINGS_H
