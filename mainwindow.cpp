#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    db=DBManager::getInstance();

    ui->setupUi(this);

    hidePassword();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    QString username = ui->name->text();
    QString password = ui->password->text();

    // Перевірка на пусті поля
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Введіть ім'я і пароль.");
        return;
    }

    // Логіка отримання користувача з бази даних
    bool isAdmin = false;
    try {
        isAdmin = db->getUser(username, password);
        qDebug()<<isAdmin;
    } catch (const std::runtime_error &error) {
        // Виведення повідомлення про помилку
        QMessageBox::warning(this, "Error", error.what());
        return;
    }

    this->resultsDialog = new ResultsDialog(isAdmin);
    resultsDialog->show();
    this->hide();

    ui->name->clear();
    ui->password->clear();
    connect(resultsDialog,&ResultsDialog::backToLogin,this,&MainWindow::show);

}




void MainWindow::on_password_returnPressed()
{
    this->on_loginButton_clicked();

}


void MainWindow::on_regiterButton_clicked()
{
    this->registrationDialog=new RegistrationDialog;
    registrationDialog->show();
}

void MainWindow::showPassword()
{
    connect(ui->showPswrd,&QPushButton::clicked,this,&MainWindow::hidePassword);
        disconnect(ui->showPswrd,&QPushButton::clicked,this,&MainWindow::showPassword);
        ui->showPswrd->setIcon(QIcon(":/img/img/hide_password_icon.png"));

        ui->password->setEchoMode(QLineEdit::Normal);
}

void MainWindow::hidePassword()
{
    connect(ui->showPswrd,&QPushButton::clicked,this,&MainWindow::showPassword);
        disconnect(ui->showPswrd,&QPushButton::clicked,this,&MainWindow::hidePassword);
        ui->showPswrd->setIcon(QIcon(":/img/img/show_password_icon.png"));

        ui->password->setEchoMode(QLineEdit::Password);
}

