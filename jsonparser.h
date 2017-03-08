#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "json.hpp"

#include <string>


namespace steamcmd {

class JsonParser : public nlohmann::json
{
public:
    JsonParser(const std::string &path);
    ~JsonParser();

protected:
    const std::string m_path;
};

} // namespace steamcmd

#endif // JSONPARSER_H
