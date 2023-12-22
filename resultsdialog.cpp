#include "resultsdialog.h"
#include "ui_resultsdialog.h"
#include <QSqlQueryModel>

ResultsDialog::ResultsDialog(bool isAdmin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultsDialog)
{
    ui->setupUi(this);
    db=DBManager::getInstance();

    if(!isAdmin){
        this->ui->addGameButton->hide();
    }

    QSqlQueryModel* model = db->getGameResultsModel();

       // Встановлення моделі для QTableView
       ui->resultsTable->setModel(model);
}

ResultsDialog::~ResultsDialog()
{
    delete ui;
}

void ResultsDialog::on_addGameButton_clicked()
{
    this->addGameDialog=new AddGameDialog;
    addGameDialog->show();
    this->hide();
}

