#ifndef SERVERWINDOW_ADDLOCALINSTALLATIONDIALOG_H
#define SERVERWINDOW_ADDLOCALINSTALLATIONDIALOG_H

#include <QFrame>
#include <QKeyEvent>


namespace Ui {
class ServerWindow_AddLocalInstallationDialog;
}

class ServerWindow_AddLocalInstallationDialog : public QFrame
{
    Q_OBJECT

public:
    explicit ServerWindow_AddLocalInstallationDialog(QWidget *parent = 0);
    ~ServerWindow_AddLocalInstallationDialog();

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_pushButtonAddLocalInstallationBrowse_clicked();

signals:
    void pathSelected(const std::string &path);

private:
    Ui::ServerWindow_AddLocalInstallationDialog *ui;
};

#endif // SERVERWINDOW_ADDLOCALINSTALLATIONDIALOG_H
