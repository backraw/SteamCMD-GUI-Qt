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
        find_steamcmd();
    }
}

void Settings::find_steamcmd()
{
    // Find the SteamCMD executable
    QProcess which;
    which.start("which steamcmd");
    which.waitForFinished();

    // Parse its output and put it as the value of key 'steamcmd'
    QByteArray output = which.readAllStandardOutput();
    (*this)["steamcmd"] = QTextCodec::codecForMib(106)->toUnicode(output.split('\n')[0]).toStdString();
}

} // namespace steamcmd
