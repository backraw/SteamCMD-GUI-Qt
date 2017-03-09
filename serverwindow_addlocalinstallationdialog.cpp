#include "serverwindow_addlocalinstallationdialog.h"
#include "ui_serverwindow_addlocalinstallationdialog.h"

ServerWindow_AddLocalInstallationDialog::ServerWindow_AddLocalInstallationDialog(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ServerWindow_AddLocalInstallationDialog)
{
    ui->setupUi(this);
}

ServerWindow_AddLocalInstallationDialog::~ServerWindow_AddLocalInstallationDialog()
{
    delete ui;
}
