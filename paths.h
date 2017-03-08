#ifndef PATHS_H
#define PATHS_H

#include <QDir>
#include <QFile>

#include <QtGlobal>


namespace steamcmd {

// Config root path
#if !defined(Q_OS_LINUX) || !defined(Q_OS_UNIX)
#error Unsupported platform!!
#else
    const QDir PATH_CONFIG(QDir::cleanPath(QDir::homePath() + "/.config"));
#endif // !defined(Q_OS_LINUX) || !defined(Q_OS_UNIX)

// Settings root path
const QDir PATH_SETTINGS(PATH_CONFIG.absolutePath() + "/steamcmd-gui-qt");

// settings.json path
const QFile PATH_SETTINGS_JSON(PATH_SETTINGS.absolutePath() + "/settings.json");

// serverlist.json path
const QFile PATH_SERVERLIST_JSON(PATH_SETTINGS.absolutePath() + "/serverlist.json");

} // namespace steamcmd

#endif // PATHS_H
