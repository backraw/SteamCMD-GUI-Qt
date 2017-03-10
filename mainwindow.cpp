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

#include "jsonparser.h"
#include "paths.h"
#include "servers.h"
#include "serverlist_updatethread.h"


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

    // Connect signals and slots
    QObject::connect(&m_server_window, SIGNAL(onClosed()), this, SLOT(on_server_window_closed()));

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
    // Clear the Server List ListWidget
    ui->listWidgetServerList->clear();

    // Create a new thread object
    QThread *thread = new QThread();

    // Create a worker and move it to the thread
    steamcmd::ServerListUpdateThread *worker = new steamcmd::ServerListUpdateThread(&m_serverlist, &m_label_status);
    worker->moveToThread(thread);

    // Connect signals and slots
    QObject::connect(worker, SIGNAL(finished()), this, SLOT(on_serverlist_updatethread_finished()));
    QObject::connect(thread, SIGNAL(started()), worker, SLOT(run()));
    QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // Start the thread
    thread->start();
}

void MainWindow::on_listWidgetServerList_doubleClicked(const QModelIndex &index)
{
    if (!m_serverlist.empty())
    {
        // Get the selected item's name
        const QString name = ui->listWidgetServerList->item(index.row())->text();

        // Prepare 'm_server_window'
        m_server_window.setServer(&m_serverlist.from_name(name.toStdString()), &m_settings);

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
    populate_serverlist_widget();

    // Reset status
    m_label_status.setText("Status: Idle");
}

void MainWindow::on_server_window_closed()
{
    // Refresh the server list widget after the ServerWindow instance has been closed
    populate_serverlist_widget();
}

void MainWindow::on_pushButtonSteamCMDExecutableFind_clicked()
{
    // Find the SteamCMD executable and store it in the settings.json file
    const QString path = QString::fromStdString(m_settings.find_steamcmd());

    // Set it as the current path
    ui->lineEditSteamCMDExecutablePath->setText(path);
}
