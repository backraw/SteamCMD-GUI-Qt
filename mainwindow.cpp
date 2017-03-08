#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_serverwindow.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QPalette>
#include <QProcess>

#include "jsonparser.h"
#include "paths.h"
#include "servers.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_label_status()
    , m_server_window()
    , m_serverlist()
    , m_settings()
{
    ui->setupUi(this);

    // Set the path to the SteamCMD executable as the text of lineEditSteamCMDExecutablePath
    ui->lineEditSteamCMDExecutablePath->setText(QString::fromStdString(m_settings["steamcmd"].get<std::string>()));

    // Setup 'm_label_status'
    m_label_status.setText("Status: Idle");
    m_label_status.setIndent(3);

    // Add 'm_label_status' to the window's status bar
    statusBar()->addWidget(&m_label_status);

    // Populate the List Widget displaying the server list
    populate_serverlist_widget();
}

MainWindow::~MainWindow()
{
    m_serverlist.clear();

    delete ui;
}

void MainWindow::populate_serverlist_widget()
{
    // Clear the List Widget displaying the server list
    ui->listWidgetServerList->clear();

    // Populate it using the contents of 'm_serverlist'
    for (auto it = m_serverlist.begin(); it != m_serverlist.end(); ++it)
    {
        ui->listWidgetServerList->addItem(QString::fromStdString(it->m_name));
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
        m_label_status.setText("Status: Path to the SteamCMD executable has been saved");
    }
}

void MainWindow::on_pushButtonServerListUpdate_clicked()
{
    // TODO: run updates in a different thread!

    // Parse https://developer.valvesoftware.com/wiki/Dedicated_Servers_List
    m_label_status.setText("Status: Parsing https://developer.valvesoftware.com/wiki/Dedicated_Servers_List...");
    m_serverlist.update();

    // Parse ~/.config/steamcmd-gui-qt/serverlist.json
    m_label_status.setText("Status: Parsing ~/.config/steamcmd-gui-qt/serverlist.json...");
    populate_serverlist_widget();

    // Reset status bar text
    m_label_status.setText("Status: Idle");
}
