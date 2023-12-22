#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include <QMessageBox>

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    db= DBManager::getInstance();
    ui->setupUi(this);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::on_registerButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString phoneNumber = ui->phoneNumberLineEdit->text();

    // Перевірка на пусті поля
    if (username.isEmpty() || password.isEmpty() || email.isEmpty() || phoneNumber.isEmpty()) {
        qDebug() << "Please fill in all fields.";
        QMessageBox::warning(this, "Error", "Заповніть всі поля.");
        return;
    }

    bool success = db->registerUser(username, password, false, email, phoneNumber);

    if (success) {
        qDebug() << "User registration successful.";
        this->close();
    } else {
        qDebug() << "User registration failed.";
    }
}


