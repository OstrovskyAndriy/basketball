#include "addgamedialog.h"
#include "ui_addgamedialog.h"

AddGameDialog::AddGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    db=DBManager::getInstance();
    fillComboBoxes();

    ui->setupUi(this);
}

AddGameDialog::~AddGameDialog()
{
    delete ui;
}

void AddGameDialog::on_addTeamButton_clicked()
{
    this->addTeamDialog = new AddTeamDialog;
    addTeamDialog->show();
}

void AddGameDialog::fillComboBoxes()
{
    QStringList teams = db->getAllTeams();

    for (const QString &team : teams) {
        qDebug() << "Team:" << team;
    }
    // Очищення вмісту ComboBox перед заповненням
        ui->team1ComboBox->clear();
        ui->team2ComboBox->clear();

        // Вставлення команд у ComboBox
        ui->team1ComboBox->addItems(teams);
        ui->team2ComboBox->addItems(teams);
}



