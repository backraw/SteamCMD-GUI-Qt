#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QPalette>

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

void MainWindow::on_lineEditSteamCMDExecutablePath_textChanged(const QString &text)
{
    // Get file information for the file path in 'text'
    QFile file(text);
    QFileInfo file_info(file);

    // Add a color palette and set text color to:
    // - Black if the file exists and is executable
    // - Red if the file does not exist or is not executable
    QPalette palette;
    palette.setColor(QPalette::Text, (file.exists() && file_info.isFile() && file_info.isExecutable()) ? Qt::black : Qt::red);

    // Update the respective LineEdit color using the palette
    ui->lineEditSteamCMDExecutablePath->setPalette(palette);
}
