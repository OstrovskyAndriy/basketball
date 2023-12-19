#ifndef ADDTEAMDIALOG_H
#define ADDTEAMDIALOG_H

#include <QDialog>
#include <player.h>
#include <vector>

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

private:
    Ui::AddTeamDialog *ui;
    std::vector<Player> players;

};

#endif // ADDTEAMDIALOG_H
