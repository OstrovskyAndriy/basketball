#include "addgamedialog.h"
#include "ui_addgamedialog.h"
#include<QMessageBox>
#include <QRegularExpression>

AddGameDialog::AddGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);

    db=DBManager::getInstance();
    fillComboBoxes();
    ui->dateEdit->setDate(QDate::currentDate());
    this->setFixedSize(this->geometry().width(), this->geometry().height());

}

AddGameDialog::~AddGameDialog()
{
    delete ui;
}

void AddGameDialog::on_addTeamButton_clicked()
{
    this->addTeamDialog = new AddTeamDialog;
    addTeamDialog->show();

    connect(addTeamDialog, &AddTeamDialog::updateComboBoxes, [=]() {
        fillComboBoxes();
    });
}

void AddGameDialog::fillComboBoxes()
{
    QMap<int, QString> teamsMap = db->getAllTeams();

    for (auto it = teamsMap.begin(); it != teamsMap.end(); ++it) {
        qDebug() << "Team ID:" << it.key() << " Team Name:" << it.value();
    }

    // Очищення вмісту ComboBox перед заповненням
    ui->teams1ComboBox->clear();
    ui->teams2ComboBox->clear();

    // Вставлення команд у ComboBox з використанням ID як додаткового даних
    for (auto it = teamsMap.begin(); it != teamsMap.end(); ++it) {
        ui->teams1ComboBox->addItem(it.value(), QVariant(it.key()));
        ui->teams2ComboBox->addItem(it.value(), QVariant(it.key()));
    }
}


void AddGameDialog::on_saveButton_clicked()
{
    // Отримання даних з комбобоксів та інших полів
    int team1Id = ui->teams1ComboBox->currentData().toInt();
    int team2Id = ui->teams2ComboBox->currentData().toInt();

    if(team1Id==team2Id){
        QMessageBox::warning(this, "Error", "Оберіть команди коректно");
        return;
    }

    QString result = ui->result->text();
    QDate gameDate = ui->dateEdit->date();
    QString location = ui->locationLineEdit->text();

    // Перевірка на пусті поля
    if (team1Id == 0 || team2Id == 0 || result.isEmpty() || location.isEmpty()) {
        QMessageBox::warning(this, "Error", "Введіть всі поля.");
        return;
    }

    // Перевірка формату результату гри
    QRegularExpression regex("\\d+:\\d+");
    if (!regex.match(result).hasMatch()) {
        QMessageBox::warning(this, "Error", "Поганй формат. Введіть в форматі 'число:число'.");
        return;
    }

    if (db->addGame(team1Id, team2Id, result, gameDate, location)) {

        QMessageBox::information(this, "Success", "Гру додано успішно.", QMessageBox::Ok);

        on_goBack_clicked();
    } else {
        qDebug() << "Failed to save game.";
    }
}


void AddGameDialog::on_goBack_clicked()
{
    this->close();
    emit goToResults();
}

