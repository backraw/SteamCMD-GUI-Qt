#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_serverwindow.h"

#include <QColor>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QPalette>
#include <QProcess>
#include <QThread>

#include "paths.h"
#include "servers.h"
#include "json/jsonparser.h"


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
    if (m_settings.count("steamcmd") > 0)
    {
        ui->lineEditSteamCMDExecutablePath->setText(QString::fromStdString(m_settings["steamcmd"].get<std::string>()));
    }

    // Request focus on it
    ui->lineEditSteamCMDExecutablePath->grabMouse();

    // Connect signals and slots
    QObject::connect(&m_server_window, SIGNAL(onClosed()), this, SLOT(on_server_window_closed()));

    // Register meta types
    qRegisterMetaType<QString>();

    // Setup 'm_label_status'
    m_label_status.setText("Status: Idle");
    m_label_status.setIndent(3);

    // Add 'm_label_status' to the window's status bar
    statusBar()->addWidget(&m_label_status);

    // Update the server list if the remote server list hasn't been cached yet
    if (!steamcmd::PATH_SERVERLIST_JSON.exists())
    {
        // Simulate a button click on 'Update'
        on_pushButtonServerListUpdate_clicked();
    }
    else
    {
        // Populate the server list widget with the cached values
        populateServerlistWidget();
    }
}

MainWindow::~MainWindow()
{
    m_serverlist.clear();

    delete ui;
}

void MainWindow::populateServerlistWidget()
{
    // Clear the List Widget displaying the server list
    ui->listWidgetServerList->clear();

    // Populate it using the contents of 'm_serverlist'
    for (auto it : m_serverlist)
    {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(it.m_name));

        if (m_settings.count(it.m_name) == 0)
        {
            item->setTextColor(QColor::fromRgb(0, 0, 0, 90));
        }

        ui->listWidgetServerList->addItem(item);
    }
}

void MainWindow::on_pushButtonSteamCMDExecutableBrowse_clicked()
{
    // Open a QFileDialog and browse to the SteamCMD executable
    // Then, store the path as the text for lineEditSteamCMDExecutablePath
    ui->lineEditSteamCMDExecutablePath->setText(QFileDialog::getOpenFileName(this, "SteamCMD Executable", QDir::homePath()));
}

void MainWindow::on_pushButtonSteamCMDExecutableFind_clicked()
{
    // Find the SteamCMD executable and store it in the settings.json file
    const QString path = QString::fromStdString(m_settings.findSteamCMD());

    // Set it as the current path
    ui->lineEditSteamCMDExecutablePath->setText(path);
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
    // Clear the Server List ListWidget
    ui->listWidgetServerList->clear();

    // Run the server list update thread
    (new steamcmd::ServerList_UpdateThread(&m_serverlist, &m_label_status))->start(this, SLOT(on_serverlist_updatethread_finished()));
}

void MainWindow::on_listWidgetServerList_doubleClicked(const QModelIndex &index)
{
    if (!m_serverlist.empty())
    {
        // Get the selected item's name
        const QString name = ui->listWidgetServerList->item(index.row())->text();

        // Prepare 'm_server_window'
        m_server_window.setup(&m_serverlist.fromName(name.toStdString()), &m_settings);

        // Show 'm_server_window'
        m_server_window.show();
    }
}

void MainWindow::on_serverlist_updatethread_finished()
{
    // Set status
    m_label_status.setText("Status: Parsing ~/.config/steamcmd-gui-qt/serverlist.json...");

    // Populate the Server List ListWidget with items parsed into
    // ~/.config/steamcmd-gui-qt/serverlist.json
    populateServerlistWidget();

    // Reset status
    m_label_status.setText("Status: Idle");
}

void MainWindow::on_server_window_closed()
{
    // Refresh the server list widget after the ServerWindow instance has been closed
    populateServerlistWidget();
}
