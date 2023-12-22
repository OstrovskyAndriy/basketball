#ifndef TEAMDIALOG_H
#define TEAMDIALOG_H

#include <QDialog>
#include <dbmanager.h>

namespace Ui {
class TeamDialog;
}

class TeamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeamDialog(const QString& teamName,QWidget *parent = nullptr);
    ~TeamDialog();

private:
    Ui::TeamDialog *ui;
    DBManager *db;
};

#endif // TEAMDIALOG_H
