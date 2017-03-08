#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>

#include "jsonparser.h"
#include  "paths.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serverlist()
    , m_settings()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    m_serverlist.clear();

    delete ui;
}

void MainWindow::parse_serverlist()
{
    // Clear 'm_serverlist'
    m_serverlist.clear();

    // Parse ~/.config/steamcmd-gui-qt/serverlist.json
    steamcmd::JsonParser serverlist(steamcmd::PATH_SERVERLIST_JSON.fileName().toStdString());

    for (auto it = serverlist.begin(); it != serverlist.end(); ++it)
    {
        // Get server details
        nlohmann::json details = it.value();

        // Add the deserialized server item to the vector of servers
        m_serverlist.push_back(steamcmd::Server(details["steamclient"].get<bool>(), details["steamcmd"].get<bool>(), details["anonymous"].get<bool>(), details["appid"].get<int>(), it.key()));
    }
}

void MainWindow::on_pushButtonSteamCMDExecutableBrowse_clicked()
{
    ui->lineEditSteamCMDExecutablePath->setText(QFileDialog::getOpenFileName(this, "SteamCMD Executable", QDir::homePath()));
}
