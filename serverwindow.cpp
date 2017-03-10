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
