#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include "serverwindow_addlocalinstallationdialog.h"
#include <QFrame>
#include <QModelIndex>

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

    void setServer(const steamcmd::Server * const server, steamcmd::Settings *settings);

private slots:
    void on_pushButtonLocalInstallationsAdd_clicked();

    void on_listWidgetLocalInstallations_clicked(const QModelIndex &index);

    void on_pushButtonLocalInstallationsRemove_clicked();

    void on_pathSelected(const std::string &path);

signals:
    void onClosed();

private:
    Ui::ServerWindow *ui;
    ServerWindow_AddLocalInstallationDialog *m_add_local_installation_dialog;

private:
    steamcmd::Settings *m_settings;
    const steamcmd::Server *m_server;
};

#endif // SERVERWINDOW_H
