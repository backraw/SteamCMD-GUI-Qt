#ifndef SERVERWINDOW_ADDLOCALINSTALLATIONDIALOG_H
#define SERVERWINDOW_ADDLOCALINSTALLATIONDIALOG_H

#include <QFrame>
#include <QKeyEvent>


namespace Ui {
class ServerWindow_AddLocalInstallationDialog;
}

/**
 * @brief window/ServerWindow_AddLocalInstallationDialog:
 *
 * Inhertis from QFrame to display a dialog to add a path to ServerWindow's Server List widget.
 */
class ServerWindow_AddLocalInstallationDialog : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief c'tor
     *
     * @param parent    A pointer to the parent ServerWindow instance
     */
    explicit ServerWindow_AddLocalInstallationDialog(QWidget *parent = 0);

    /**
     * @brief d'tor
     *
     * Run memory cleanup tasks.
     */
    ~ServerWindow_AddLocalInstallationDialog();

protected:
    /**
     * @brief Override QFrame's keyPressEvent() to notice whether the Return key has been pressed.
     *
     * @param e A pointer to a QKeyEvent holding information about the event happening at the moment of execution
     */
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_pushButtonAddLocalInstallationBrowse_clicked();
    void on_pushButtonAddLocalInstallationOK_clicked();

signals:
    /**
     * @brief signal/pathSelected:
     *
     * Used to signal to ServerWindow that a path has been selected and should be added to its Server List widget.
     *
     * @param path A constant reference to a std::string holding the path the user wants to add to ServerWindow's Server List widget
     *
     */
    void pathSelected(const std::string &path);

private:
    Ui::ServerWindow_AddLocalInstallationDialog *ui;
};

#endif // SERVERWINDOW_ADDLOCALINSTALLATIONDIALOG_H
