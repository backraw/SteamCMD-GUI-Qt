#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "json.hpp"

#include <string>


namespace steamcmd {

/**
 * @brief steamcmd::JsonParser
 *
 * Inherits from nlohmann::json and utilizes the c'tor and d'tor
 * to save and write the json file, respectively.
 */
class JsonParser : public nlohmann::json
{
public:
    /**
     * @brief c'tor:
     * Open the json file 'path'.
     *
     * @param path The path to the json file which will be parsed into this object
     */
    JsonParser(const std::string &path);

    /**
     * @brief d'tor:
     * Write the json file with this object's contents.
     */
    ~JsonParser();

protected:
    const std::string m_path;   ///< Holds the path to a json file
};

} // namespace steamcmd

#endif // JSONPARSER_H
