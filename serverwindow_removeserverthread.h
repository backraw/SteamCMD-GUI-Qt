#ifndef SERVERWINDOW_REMOVESERVERTHREAD_H
#define SERVERWINDOW_REMOVESERVERTHREAD_H

#include <QDir>
#include <QObject>
#include <QWidget>

#include <string>


namespace steamcmd {

class ServerWindow_RemoveServerThread : public QObject
{
    Q_OBJECT
public:
    explicit ServerWindow_RemoveServerThread(const QDir directory, QObject *parent = 0);

public slots:
    void run();

signals:
    void finished(const QString directory);

private:
    const QDir m_directory;
};

} // namespace steamcmd

#endif // SERVERWINDOW_REMOVESERVERTHREAD_H
