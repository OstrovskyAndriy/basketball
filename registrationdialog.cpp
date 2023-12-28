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
        QMessageBox::warning(this, "Error", "Заповніть всі поля.");
        return;
    }

    // Перевірка, чи email має символ '@'
    if (!email.contains('@')) {
        QMessageBox::warning(this, "Error", "Невірний формат email.");
        return;
    }

    try {
        this->user = new User(username, password, false, email, phoneNumber);
        db->registerUser(*user);
        this->close();
    } catch (const std::runtime_error &error) {
        QMessageBox::warning(this, "Error", error.what());
    }
}



