#include "serverwindow.h"
#include "ui_serverwindow.h"

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

void ServerWindow::setServer(const steamcmd::Server * const server)
{
    m_server = server;
    setWindowTitle(QString::fromStdString(server->m_name));
}
