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
    delete addTeamDialog;
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
//        ui->teams1ComboBox->clear();
//        ui->teams2ComboBox->clear();

        // Вставлення команд у ComboBox
        ui->teams1ComboBox->addItems(teams);
        ui->teams2ComboBox->addItems(teams);
}
