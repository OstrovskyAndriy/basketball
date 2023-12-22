#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include <addteamdialog.h>
#include <dbmanager.h>
#include <QComboBox>

namespace Ui {
class AddGameDialog;
}

class AddGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGameDialog(QWidget *parent = nullptr);
    ~AddGameDialog();

private slots:
    void on_addTeamButton_clicked();
    void fillComboBoxes();

    void on_saveButton_clicked();

    void on_goBack_clicked();

signals:
    void goToResults();

private:
    Ui::AddGameDialog *ui;

    AddTeamDialog*addTeamDialog;
    DBManager *db;


};

#endif // ADDGAMEDIALOG_H
