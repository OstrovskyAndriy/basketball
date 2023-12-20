#include "registrationdialog.h"
#include "ui_registrationdialog.h"
//#include <QRegExp>

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
        // Додайте код для відображення повідомлення користувачу про невалідні дані
        return;
    }

    // Перевірка формату email (можете використовувати більш складні перевірки за допомогою регулярних виразів)
//    QRegExp emailRegex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
//    if (!emailRegex.exactMatch(email)) {
//        qDebug() << "Invalid email format.";
//        // Додайте код для відображення повідомлення користувачу про невалідний email
//        return;
//    }

//    // Перевірка формату номера телефону (можете використовувати більш складні перевірки за допомогою регулярних виразів)
//    QRegExp phoneRegex(R"(\b\d{10}\b)");
//    if (!phoneRegex.exactMatch(phoneNumber)) {
//        qDebug() << "Invalid phone number format.";
//        // Додайте код для відображення повідомлення користувачу про невалідний номер телефону
//        return;
//    }

    bool success = db->registerUser(username, password, false, email, phoneNumber);

    if (success) {
        qDebug() << "User registration successful.";
        this->close();
    } else {
        qDebug() << "User registration failed.";
    }
}


