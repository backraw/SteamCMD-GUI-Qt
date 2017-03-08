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

    // Set the path to the SteamCMD executable as the text of lineEditSteamCMDExecutablePath
    ui->lineEditSteamCMDExecutablePath->setText(QString::fromStdString(m_settings["steamcmd"].get<std::string>()));
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

        // Add the title to the List Widget displaying the server list
        ui->listWidgetServerList->addItem(QString::fromStdString(it.key()));
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

    const bool is_executable = file.exists() && file_info.isFile() && file_info.isExecutable();

    // Add a color palette and set text color to:
    // - Black if the file exists and is executable
    // - Red if the file does not exist or is not executable
    QPalette palette;
    palette.setColor(QPalette::Text, is_executable ? Qt::black : Qt::red);

    // Update the respective LineEdit color using the palette
    ui->lineEditSteamCMDExecutablePath->setPalette(palette);

    // Store the new text as the value of 'steamcmd' in ~/.config/steamcmd-gui-qt/settings.json if the file is executable
    if (is_executable)
    {
        m_settings["steamcmd"] = text.toStdString();
    }
}
