#include "addteamdialog.h"
#include "ui_addteamdialog.h"
#include <QMessageBox>

AddTeamDialog::AddTeamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeamDialog)
{
    db=DBManager::getInstance();
    ui->setupUi(this);
}

AddTeamDialog::~AddTeamDialog()
{
    delete ui;
}

void AddTeamDialog::on_addPlayer_clicked()
{

    QString name = ui->playerName->text();
    QString surname = ui->playerSurname->text();
    QString heightS = ui->playerHeight->text();

    // Перевірка на пусті поля
    if (name.isEmpty() || surname.isEmpty() || heightS.isEmpty() ) {
        QMessageBox::warning(this, "Error", "Заповніть всі поля.");
        return;
    }

    // Перевірка на int для перемог і програшів
    bool winsOk;
    int height = heightS.toInt(&winsOk);

    if (!winsOk) {
        QMessageBox::warning(this, "Error", "Ріст повинен бути int.");
        return;
    }

    // Створення гравця і додавання його до вектору
    Player player(name, surname, height);
    players.push_back(player);

    // Очищення полів форми
    ui->playerName->clear();
    ui->playerSurname->clear();
    ui->playerHeight->clear();
    playersCount++;

}



void AddTeamDialog::on_saveButton_clicked()
{

    if(playersCount>=3&&playersCount<=10){
        QString winsS = ui->teamWins->text();
        QString losesS = ui->teamLoses->text();
        QString teamName = ui->teamName->text();

        // Перевірка на пусті поля
        if (winsS.isEmpty() || losesS.isEmpty() || teamName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Заповніть всі поля.");
            return;
        }

        // Перевірка на int для перемог і програшів
        bool winsOk, losesOk;
        int wins = winsS.toInt(&winsOk);
        int loses = winsS.toInt(&losesOk);

        if (!winsOk||!losesOk) {
            QMessageBox::warning(this, "Error", "Виграші і програші повинні бути int.");
            return;
        }
        db->addTeam(teamName,players,wins,loses);
        this->hide();
        emit updateComboBoxes();
    }
    else{
        QMessageBox::warning(this, "Error", "Гравців повинно бути мінімум 5 і максимум 10.");

    }
}

