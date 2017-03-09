#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QDir>
#include <QFileDialog>


ServerWindow::ServerWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ServerWindow)
    , m_settings(nullptr)
    , m_server(nullptr)
{
    ui->setupUi(this);

    // Disable the button 'Remove' on object creation
    ui->pushButtonLocalInstallationsRemove->setDisabled(true);
}

ServerWindow::~ServerWindow()
{
    m_server = nullptr;
    m_settings = nullptr;

    delete ui;
}

void ServerWindow::setServer(const steamcmd::Server * const server, const steamcmd::Settings *settings)
{
    m_server = server;
    m_settings = settings;

    setWindowTitle(QString::fromStdString(server->m_name));
}

void ServerWindow::on_pushButtonLocalInstallationsAdd_clicked()
{
}
