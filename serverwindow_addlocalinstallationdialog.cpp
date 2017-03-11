#include "serverwindow_addlocalinstallationdialog.h"
#include "ui_serverwindow_addlocalinstallationdialog.h"

#include <QFileDialog>


ServerWindow_AddLocalInstallationDialog::ServerWindow_AddLocalInstallationDialog(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ServerWindow_AddLocalInstallationDialog)
{
    ui->setupUi(this);

    // Request the focus for the line edit
    ui->lineEditAddLocalInstallationPath->grabMouse();
}

ServerWindow_AddLocalInstallationDialog::~ServerWindow_AddLocalInstallationDialog()
{
    delete ui;
}

void ServerWindow_AddLocalInstallationDialog::keyPressEvent(QKeyEvent *e)
{
    // Simulate a button press on 'OK' after the Return key was pressed
    if (e->key() == Qt::Key_Return)
    {
        on_pushButtonAddLocalInstallationOK_clicked();
    }
}

void ServerWindow_AddLocalInstallationDialog::on_pushButtonAddLocalInstallationBrowse_clicked()
{
    // Open a QFileDialog to browse to a folder and set its path as the text of
    // lineEditAddLocalInstallationPath
    ui->lineEditAddLocalInstallationPath->setText(QFileDialog::getExistingDirectory(this, "Add Local Installation", QDir::home().absolutePath()));
}

void ServerWindow_AddLocalInstallationDialog::on_pushButtonAddLocalInstallationOK_clicked()
{
    // Emit the signal 'pathSelected'
    emit pathSelected(ui->lineEditAddLocalInstallationPath->text().toStdString());

    // Close this window
    close();
}
