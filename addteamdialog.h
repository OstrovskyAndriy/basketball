#ifndef ADDTEAMDIALOG_H
#define ADDTEAMDIALOG_H

#include <QDialog>
#include <player.h>
#include <vector>
#include <dbmanager.h>

namespace Ui {
class AddTeamDialog;
}

class AddTeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeamDialog(QWidget *parent = nullptr);
    ~AddTeamDialog();

private slots:
    void on_addPlayer_clicked();

    void on_saveButton_clicked();

signals:
    void updateComboBoxes();

private:
    Ui::AddTeamDialog *ui;
    std::vector<Player> players;

    DBManager *db;

    int playersCount=0;

};

#endif // ADDTEAMDIALOG_H
