#include "serverwindow_removeserverthread.h"

#include <QMessageBox>
#include <QProcess>


namespace steamcmd {

ServerWindow_RemoveServerThread::ServerWindow_RemoveServerThread(const QDir directory, QObject *parent)
    : QObject(parent)
    , m_directory(directory)
{
}

void ServerWindow_RemoveServerThread::run()
{
    const QString path = m_directory.absolutePath();

    // Remove 'm_directory' from the file system if it exists
    if (m_directory.exists())
    {
        // Start the 'rm -rf' process
        QProcess rm;
        rm.start("rm -rf " + path);
        rm.waitForFinished(-1);
    }

    emit finished(path);
}

} // namespace steamcmd
