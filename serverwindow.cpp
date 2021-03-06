#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QThread>


// Define how much to add to the initial window height
// if a Steam logon is required
#define INITIAL_HEIGHT_ADD      70

// Define how much to subtract from the initial window height
// if a Steam logon is not required
#define INITIAL_HEIGHT_SUBTRACT 190


ServerWindow::ServerWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ServerWindow)
    , m_add_local_installation_dialog()
    , m_settings(nullptr)
    , m_server(nullptr)
    , m_initial_height(size().height() - INITIAL_HEIGHT_SUBTRACT)
{
    ui->setupUi(this);

    // Disable the buttons 'Remove'
    ui->pushButtonLocalInstallationsRemove->setDisabled(true);

    // Clear the list view
    ui->listWidgetLocalInstallations->clear();

    // Connect signals and slots
    QObject::connect(&m_add_local_installation_dialog, SIGNAL(pathSelected(std::string)), this, SLOT(on_pathSelected(std::string)));
}

ServerWindow::~ServerWindow()
{
    m_server = nullptr;
    m_settings = nullptr;

    delete ui;
}

void ServerWindow::setup(const steamcmd::Server * const server, steamcmd::Settings *settings)
{
    // Refresh members
    m_server = server;
    m_settings = settings;

    // Set the window title to the server's name
    setWindowTitle(QString::fromStdString(server->m_name));

    // Refresh the list view
    ui->listWidgetLocalInstallations->clear();

    if (settings->count(server->m_name) > 0)
    {
        for (auto it : (*settings)[server->m_name])
        {
            ui->listWidgetLocalInstallations->addItem(QString::fromStdString(it.get<std::string>()));
        }

        ui->listWidgetLocalInstallations->setItemSelected(ui->listWidgetLocalInstallations->item(0), true);
        on_listWidgetLocalInstallations_clicked(ui->listWidgetLocalInstallations->indexAt(QPoint(0, 0)));
    }

    // Resize the window, respecting the server's 'anonymous' value
    resize(size().width(), (!server->m_anonymous) ? m_initial_height + INITIAL_HEIGHT_ADD : m_initial_height);
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
    m_add_local_installation_dialog.show();
}

void ServerWindow::on_listWidgetLocalInstallations_clicked(const QModelIndex &index)
{
    // Enable the button 'Remove'
    ui->pushButtonLocalInstallationsRemove->setDisabled(false);

    // Get rid of the compiler warning that says 'index' is unused
    static_cast<void>(index);
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

            // Ask if the folder should be recursively removed from the file system
            if (QMessageBox::question(this, "Remove server files?",
                                      "Clicking 'Yes' will recursively remove the folder from the file system!!",
                                      QMessageBox::No|QMessageBox::Yes) == QMessageBox::Yes)
            {
                (new steamcmd::ServerWindow_RemoveServerThread(QDir(QString::fromStdString(text))))->start(this, SLOT(on_removeserverthread_finished(QString)));
            }
        }
    }
}

void ServerWindow::on_listWidgetLocalInstallations_doubleClicked(const QModelIndex &index)
{
    // Generate command string
    QStringList arguments;
    arguments << "-e" << QString::fromStdString((*m_settings)["steamcmd"].get<std::string>()) << "+login";

    if (m_server->m_anonymous)
    {
        arguments << "anonymous";
    }
    else
    {
        arguments << ui->lineEditLoginUsername->text();
    }

    arguments << "+force_install_dir";

    // Add AppID information
    arguments << ui->listWidgetLocalInstallations->item(index.row())->text() << "+app_update" << QString::number(m_server->m_appid) << "validate" << "+quit";

    // Run the process using 'xterm -e'
    QProcess steamcmd;
    steamcmd.startDetached("xterm", arguments);
    steamcmd.waitForFinished(-1);
}

void ServerWindow::on_pathSelected(const std::string &path)
{
    // Get a QString object from 'path'
    const QString qpath = QString::fromStdString(path);
    const QDir dir = QDir(qpath);

    if (dir.exists() && !dir.isRoot() && QFileInfo(dir.absolutePath()).isWritable())
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

void ServerWindow::on_removeserverthread_finished(const QString &directory)
{
    // Display a QMessageBox to the user, if the folder still exists
    if (QDir(directory).exists())
    {
        QMessageBox::question(this, "Could not remove directory!", directory + " could not be recursively removed by 'rm'!", QMessageBox::Ok);
    }
}


namespace steamcmd {

ServerWindow_RemoveServerThread::ServerWindow_RemoveServerThread(const QDir directory, QObject *parent)
    : Thread(parent)
    , m_directory(directory)
{
}

void ServerWindow_RemoveServerThread::start(const QObject *receiver, const char *slot)
{
    startWithSignal(SIGNAL(finished(QString)), receiver, slot);
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
