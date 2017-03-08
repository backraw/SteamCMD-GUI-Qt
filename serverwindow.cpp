#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QDir>
#include <QFileDialog>


ServerWindow::ServerWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ServerWindow)
    , m_server(nullptr)
{
    ui->setupUi(this);
}

ServerWindow::~ServerWindow()
{
    m_server = nullptr;
    delete ui;
}

void ServerWindow::setServer(const steamcmd::Server * const server, const steamcmd::Settings *settings)
{
    m_server = server;
    m_settings = settings;

    setWindowTitle(QString::fromStdString(server->m_name));
}

void ServerWindow::on_pushButtonLocalInstallationBrowse_clicked()
{
    ui->lineEditLocalInstallationPath->setText(QFileDialog::getExistingDirectory(this, QString::fromStdString(m_server->m_name) + ": Server Installation Path", QDir::homePath()));
}
