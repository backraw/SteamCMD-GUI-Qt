#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serverlist()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    m_serverlist.clear();

    delete ui;
}
