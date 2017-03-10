#include "serverwindow_addlocalinstallationdialog.h"
#include "ui_serverwindow_addlocalinstallationdialog.h"

#include <QFileDialog>


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

void ServerWindow_AddLocalInstallationDialog::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return)
    {
        on_pushButtonAddLocalInstallationOK_clicked();
    }
}

void ServerWindow_AddLocalInstallationDialog::on_pushButtonAddLocalInstallationBrowse_clicked()
{
    ui->lineEditAddLocalInstallationPath->setText(QFileDialog::getExistingDirectory(this, "Add Local Installation", QDir::home().absolutePath()));
}
