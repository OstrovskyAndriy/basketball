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
    QString email = ui->email->text();
    QString password = ui->password->text();

    // Перевірка на пусті поля
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Введіть email і пароль.");
        return;
    }

    // Перевірка, чи email має символ '@'
    if (!email.contains('@')) {
        QMessageBox::warning(this, "Error", "Невірний формат email.");
        return;
    }

    try {
        User user = db->getUser(email, password);

        bool isAdmin = user.isAdmin();

        this->resultsDialog = new ResultsDialog(isAdmin);
        resultsDialog->show();
        this->hide();

        ui->email->clear();
        ui->password->clear();
        connect(resultsDialog, &ResultsDialog::backToLogin, this, &MainWindow::show);
    } catch (const std::runtime_error &error) {
        // Виведення повідомлення про помилку
        QMessageBox::warning(this, "Error", error.what());
    }
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

