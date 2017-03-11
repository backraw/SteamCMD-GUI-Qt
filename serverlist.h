#ifndef SERVERLIST_H
#define SERVERLIST_H

#include "servers.h"

#include <QLabel>
#include <QObject>

#include <string>
#include <vector>


namespace steamcmd {

/**
 * @brief steamcmd::ServerList:
 *
 * Inherits from std::vector<steamcmd::Server> to hold steamcmd::Server instances and
 * provide more functions we need.
 */
class ServerList : public std::vector<Server>
{
public:
    /**
     * @brief c'tor
     *
     * Run update() if ~/.config/steamcmd-gui-qt/serverlist.json doesn't exist
     * Always run parse() [after update()]
     */
    ServerList();

    /**
     * @brief Convert each server in ~/.config/steamcmd-gui-qt/serverlist.json to a
     * steamcmd::Server instance and put it in this vector.
     */
    void parse();

    /**
     * @brief Parse https://developer.valvesoftware.com/wiki/Dedicated_Servers_List
     * into ~/.config/steamcmd-gui-qt/serverlist.json.
     */
    void update();

    /**
     * @brief Return a reference to a steamcmd::Server instance found in this vector by name.
     *
     * @param name The name of the server to be found
     *
     * @return A reference to the steamcmd::Server instance found in this vector
     */
    Server &fromName(const std::string &name);
};


/**
 * @brief thread/ServerList_UpdateThread:
 *
 * Used to run the script serverlist.py using QProcess.
 * An object of this class shall be moved to a QThread instance via \<thread\>->moveToThread().
 */
class ServerList_UpdateThread : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief c'tor
     *
     * @param serverlist    A pointer to MainWindow's steamcmd::ServerList instance
     * @param label_status  A pointer to MainWindow's status bar label
     * @param parent        A pointer to the parent QObject (always 0)
     */
    ServerList_UpdateThread(ServerList *serverlist, QLabel *label_status, QObject *parent = 0);

public slots:
    /**
     * @brief Run the script serverlist.py using QProcess
     */
    void run();

signals:
    /**
     * @brief signal/finished:
     *
     * Used to signal to MainWindow that the QProcess started by run() has finished.
     */
    void finished();

private:
    ServerList *m_serverlist;
    QLabel *m_label_status;
};

} // namespace steamcmd

#endif // SERVERLIST_H
