#include <QByteArray>
#include <QFile>
#include <QProcess>
#include <QString>
#include <QTextCodec>

#include "settings.h"
#include "paths.h"


namespace steamcmd {

Settings::Settings()
    : JsonParser(PATH_SETTINGS_JSON.fileName().toStdString())
{
    const bool path_exists = QFile(QString::fromStdString(m_path)).exists();

    // Find the SteamCMD executable if it is not set in
    // ~/.config/steamcmd-gui-qt/settings.json
    if (!path_exists || (path_exists && !QFile(QString::fromStdString(((*this)["steamcmd"]).get<std::string>())).exists()))
    {
        findSteamCMD();
    }
}

const std::string Settings::findSteamCMD(const std::string executable, const int tries)
{
    // Find the SteamCMD executable
    QProcess which;
    which.start(QString::fromStdString("which " + executable));
    which.waitForFinished();

    // Parse its output
    QByteArray output = which.readAllStandardOutput();
    const std::string path = QTextCodec::codecForMib(106)->toUnicode(output.split('\n')[0]).toStdString();

    // If empty, look for 'steamcmd.sh'
    if (path.empty() && tries < 2)
    {
        return findSteamCMD("steamcmd.sh", tries + 1);
    }

    // Return the path found
    return path;
}

} // namespace steamcmd
