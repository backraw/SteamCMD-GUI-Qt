#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QDir>
#include <QFileDialog>


ServerWindow::ServerWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ServerWindow)
    , m_add_local_installation_dialog(nullptr)
    , m_settings(nullptr)
    , m_server(nullptr)
{
    ui->setupUi(this);

    // Disable the button 'Remove' on object creation
    ui->pushButtonLocalInstallationsRemove->setDisabled(true);

    // Clear the list view
    ui->listWidgetLocalInstallations->clear();
}

ServerWindow::~ServerWindow()
{
    if (m_add_local_installation_dialog != nullptr)
    {
        delete m_add_local_installation_dialog;
    }

    m_add_local_installation_dialog = nullptr;
    m_server = nullptr;
    m_settings = nullptr;

    delete ui;
}

void ServerWindow::setServer(steamcmd::Server *server, steamcmd::Settings *settings)
{
    if (m_add_local_installation_dialog != nullptr)
    {
        delete m_add_local_installation_dialog;
    }

    m_add_local_installation_dialog = new ServerWindow_AddLocalInstallationDialog();

    m_server = server;
    m_settings = settings;

    setWindowTitle(QString::fromStdString(server->m_name));

    // Refresh the list view
    ui->listWidgetLocalInstallations->clear();

    if (settings->count(server->m_name) > 0)
    {
        for (auto it : (*settings)[server->m_name])
        {
            ui->listWidgetLocalInstallations->addItem(QString::fromStdString(it.get<std::string>()));
        }
    }
}

void ServerWindow::on_pushButtonLocalInstallationsAdd_clicked()
{
    m_add_local_installation_dialog->show();
}

void ServerWindow::on_listWidgetLocalInstallations_clicked(const QModelIndex &index)
{
    // Enable the button 'Remove'
    ui->pushButtonLocalInstallationsRemove->setDisabled(false);
}

void ServerWindow::on_pushButtonLocalInstallationsRemove_clicked()
{
    // Remove the selected ListWidget item
    ui->listWidgetLocalInstallations->removeItemWidget(ui->listWidgetLocalInstallations->selectedItems().at(0));
}

void ServerWindow::on_pathSelected(const std::string &path)
{
    // Get a QString object from 'path'
    const QString qpath = QString::fromStdString(path);

    if (QDir(qpath).exists())
    {
        // Add the path to the list widget
        ui->listWidgetLocalInstallations->addItem(qpath);

        // Create an entry for the server in
        // ~/.config/steamcmd-gui-qt/settings.json if necessary
        if (m_settings->count(m_server->m_name) == 0)
        {
            (*m_settings)[m_server->m_name] = nlohmann::json::array();
        }

        // Add the path to the server entry in the json file
        // if the entry doesn't exist yet
        nlohmann::json &j = (*m_settings)[m_server->m_name];

        if (j.count(path) == 0)
        {
            j.push_back(path);
        }
    }
}
