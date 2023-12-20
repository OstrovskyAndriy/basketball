#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <dbmanager.h>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

private slots:
    void on_registerButton_clicked();

private:
    Ui::RegistrationDialog *ui;

    DBManager *db;
};

#endif // REGISTRATIONDIALOG_H
