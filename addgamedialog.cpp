#include "addgamedialog.h"
#include "ui_addgamedialog.h"

AddGameDialog::AddGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{

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

