#include "jsonparser.h"

#include <fstream>

#include <QFile>


namespace steamcmd {

JsonParser::JsonParser(const std::string &path)
    : nlohmann::json()
    , m_path(path)
{
    // Open json file for reading
    std::ifstream file(m_path);

    // Add its contents if the file is good
    if (file.good())
    {
        file >> *this;
    }

    // Close the json file
    file.close();
}

JsonParser::~JsonParser()
{
    // Open json file for writing
    std::ofstream file(m_path);

    // Write pretty-printed contents of this object
    file << std::setw(4) << *this << std::endl;

    // Close the json file
    file.close();
}

} // namespace steamcmd
