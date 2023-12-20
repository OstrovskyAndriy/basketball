#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    db=DBManager::getInstance();

    ui->setupUi(this);
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
        QMessageBox::warning(this, "Error", "Please enter both username and password.");
        return;
    }

    // Логіка отримання користувача з бази даних
    bool isAdmin = false;
    try {
        isAdmin = db->getUser(username, password);
    } catch (const std::runtime_error &error) {
        // Виведення повідомлення про помилку
        QMessageBox::warning(this, "Error", error.what());
        return;
    }

    this->resultsDialog = new ResultsDialog(isAdmin);
    resultsDialog->show();
    this->hide();


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

