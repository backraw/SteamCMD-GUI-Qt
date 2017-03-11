#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include "serverwindow_addlocalinstallationdialog.h"

#include <QCloseEvent>
#include <QDir>
#include <QFrame>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QWidget>

#include <string>

#include "servers.h"
#include "settings.h"


namespace Ui {
class ServerWindow;
}

/**
 * @brief window/ServerWindow:
 *
 * A window containing detailed information about a server's local installations.
 */
class ServerWindow : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief c'tor
     *
     * @param parent The parent QWidget for this window (always a pointer to the MainWindow instance)
     */
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

    /**
     * @brief Setup the window with server information
     *
     * @param server    A constant pointer to a steamcmd::Server instance
     * @param settings  A pointer to MainWindow's steamcmd::Settings instance
     */
    void setup(const steamcmd::Server * const server, steamcmd::Settings *settings);

protected:
    /**
     * @brief Listen to QFrame's close event for this class.
     *
     * @param e A pointer to the QCloseEvent happening at the moment of execution
     */
    void closeEvent(QCloseEvent *e);

private slots:
    void on_pushButtonLocalInstallationsAdd_clicked();
    void on_pushButtonLocalInstallationsRemove_clicked();

    void on_listWidgetLocalInstallations_clicked(const QModelIndex &index);

    void on_pathSelected(const std::string &path);
    void on_removeserverthread_finished(const QString &directory);

    void on_listWidgetLocalInstallations_doubleClicked(const QModelIndex &index);

signals:
    /**
     * @brief signal/onClosed:
     *
     * Used to signal to MainWindow that this window has been closed by the user.
     */
    void onClosed();

private:
    Ui::ServerWindow *ui;
    ServerWindow_AddLocalInstallationDialog *m_add_local_installation_dialog;

private:
    steamcmd::Settings *m_settings;
    const steamcmd::Server *m_server;

    const int m_initial_height;
};


namespace steamcmd {

/**
 * @brief thread/ServerWindow_RemoveServerThread:
 *
 * Used to remove a directory from the filesystem using QProcess.
 * An object of this class shall be moved to a QThread instance via \<thread\>->moveToThread().
 */
class ServerWindow_RemoveServerThread : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief c'tor
     *
     * @param directory A QDir instance for the directory to be removed
     * @param parent    A pointer to the parent QObject instance (always 0)
     */
    explicit ServerWindow_RemoveServerThread(const QDir directory, QObject *parent = 0);

public slots:
    /**
     * @brief slot/run:
     *
     * Run a QProcess to remove 'm_directory' using 'rm -rf'.
     */
    void run();

signals:
    /**
     * @brief signal/finished:
     *
     * Used to signal to MainWindow's ServerWindow instance that the QProcess started by run() has finished.
     *
     * @param directory A QString holding the path in 'm_directory'
     */
    void finished(const QString directory);

private:
    const QDir m_directory;     ///< A QDir instance representing the directory to be removed
};

} // namespace steamcmd

#endif // SERVERWINDOW_H
