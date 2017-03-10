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

void ServerWindow::setup(const steamcmd::Server * const server, steamcmd::Settings *settings)
{
    if (m_add_local_installation_dialog != nullptr)
    {
        delete m_add_local_installation_dialog;
    }

    m_add_local_installation_dialog = new ServerWindow_AddLocalInstallationDialog();
    QObject::connect(m_add_local_installation_dialog, SIGNAL(pathSelected(std::string)), this, SLOT(on_pathSelected(std::string)));

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

void ServerWindow::closeEvent(QCloseEvent *e)
{
    // Emit the signal 'onClosed'
    emit onClosed();

    // Call the base class method
    QFrame::closeEvent(e);
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
    // Loop through all items in the list widget
    for (int i = 0; i < ui->listWidgetLocalInstallations->count(); i++)
    {
        // Get the item at the current row
        QListWidgetItem *item = ui->listWidgetLocalInstallations->item(i);

        // Handle item removal if the item is selected
        if (item->isSelected())
        {
            // Remove it from the list widget
            ui->listWidgetLocalInstallations->takeItem(i);

            // Get the list widget's text
            const std::string text = item->text().toStdString();

            // Remove the path from settings.json
            if (m_settings->count(m_server->m_name) > 0)
            {
                (*m_settings)[m_server->m_name].erase((*m_settings)[m_server->m_name].find(text));
            }

            // If the array of paths is empty, remove the server from settings.json
            if ((*m_settings)[m_server->m_name].size() == 0)
            {
                m_settings->erase(m_settings->find(m_server->m_name));
            }
        }
    }
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
