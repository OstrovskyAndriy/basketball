#include "resultsdialog.h"
#include "ui_resultsdialog.h"

ResultsDialog::ResultsDialog(bool isAdmin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultsDialog)
{
    if(!isAdmin){
        ui->addgame->hide();
    }


    ui->setupUi(this);
}

ResultsDialog::~ResultsDialog()
{
    delete ui;
}

void ResultsDialog::on_addgame_clicked()
{
    this->addGameDialog=new AddGameDialog;
    addGameDialog->show();
    this->hide();
}

