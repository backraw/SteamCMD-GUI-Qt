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

class ServerWindow : public QFrame
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

    void setup(const steamcmd::Server * const server, steamcmd::Settings *settings);

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_pushButtonLocalInstallationsAdd_clicked();
    void on_pushButtonLocalInstallationsRemove_clicked();

    void on_listWidgetLocalInstallations_clicked(const QModelIndex &index);

    void on_lineEditLoginUsername_textChanged(const QString &text);

    void on_pathSelected(const std::string &path);
    void on_removeserverthread_finished(const QString &directory);

signals:
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

#endif // SERVERWINDOW_H
