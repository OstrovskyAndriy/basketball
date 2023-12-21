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
    QString winsStr = ui->playerWins->text();
    QString lossesStr = ui->playerLoses->text();

    // Перевірка на пусті поля
    if (name.isEmpty() || surname.isEmpty() || winsStr.isEmpty() || lossesStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Заповніть всі поля.");
        return;
    }

    // Перевірка на int для перемог і програшів
    bool winsOk, lossesOk;
    int wins = winsStr.toInt(&winsOk);
    int losses = lossesStr.toInt(&lossesOk);

    if (!winsOk || !lossesOk) {
        QMessageBox::warning(this, "Error", "Перемоги та програші повинні бути int.");
        return;
    }

    // Створення гравця і додавання його до вектору
    Player player(name, surname, wins, losses);
    players.push_back(player);

    // Очищення полів форми
    ui->playerName->clear();
    ui->playerSurname->clear();
    ui->playerWins->clear();
    ui->playerLoses->clear();
    playersCount++;

}



void AddTeamDialog::on_saveButton_clicked()
{
    if(playersCount>=5&&playersCount<=10){
        db->addTeam(ui->teamName->text(),players);
        this->hide();
        emit updateComboBoxes();
    }
    else{
        QMessageBox::warning(this, "Error", "Гравців повинно бути мінімум 5 і максимум 10.");

    }
}

