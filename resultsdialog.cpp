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
    setTableModel();
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

//    connect(addGameDialog,&AddGameDialog::goToResults,this,&ResultsDialog::show);
    connect(addGameDialog, &AddGameDialog::goToResults, [this]() {
        this->setTableModel();
        this->show();
    });

}


void ResultsDialog::on_getBackButton_clicked()
{

    emit backToLogin();
    this->close();
}

void ResultsDialog::setTableModel()
{
    QSqlQueryModel* model = db->getGameResultsModel();

    // Встановлення моделі для QTableView
    ui->resultsTable->setModel(model);
    ui->resultsTable->verticalHeader()->setVisible(false);


    // Встановлення ширини кожної з 5-ти колонок
    for (int i = 0; i < model->columnCount(); ++i) {
        ui->resultsTable->setColumnWidth(i, (this->width()-25) / model->columnCount());
    }

    this->setFixedSize(this->geometry().width(), this->geometry().height() - 23);
    ui->resultsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


