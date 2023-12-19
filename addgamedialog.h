#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include <addteamdialog.h>


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

private:
    Ui::AddGameDialog *ui;

    AddTeamDialog*addTeamDialog;


};

#endif // ADDGAMEDIALOG_H
