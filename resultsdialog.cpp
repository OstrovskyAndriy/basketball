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

    // Встановлення моделі таблиці для QTableView
    ui->resultsTable->setModel(model);
    ui->resultsTable->verticalHeader()->setVisible(false);


    setModelSettings(*model);

    fillComboBoxes();
}





void ResultsDialog::on_teamsComboBox_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel* model = db->getGameResultsModel(arg1);

    ui->resultsTable->setModel(model);
    ui->resultsTable->verticalHeader()->setVisible(false);
    setModelSettings(*model);
}

void ResultsDialog::fillComboBoxes()
{
    QMap<int, QString> teamsMap = db->getAllTeams();

    for (auto it = teamsMap.begin(); it != teamsMap.end(); ++it) {
        qDebug() << "Team ID:" << it.key() << " Team Name:" << it.value();
    }

    // Очищення вмісту ComboBox перед заповненням
    ui->teamsComboBox->clear();
    ui->teamsComboBox->addItem("");

    // Вставлення команд у ComboBox з використанням ID як додаткового даних
    for (auto it = teamsMap.begin(); it != teamsMap.end(); ++it) {
        ui->teamsComboBox->addItem(it.value(), QVariant(it.key()));
    }
}

void ResultsDialog::setModelSettings(QSqlQueryModel &model)
{
    // Встановлення ширини кожної з 5-ти колонок
    for (int i = 0; i < model.columnCount(); ++i) {
        ui->resultsTable->setColumnWidth(i, (this->width()-25) / model.columnCount());
    }

    this->setFixedSize(this->geometry().width(), this->geometry().height() - 23);
    ui->resultsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void ResultsDialog::on_resultsTable_doubleClicked(const QModelIndex &index)
{
    QString teamName = ui->resultsTable->model()->data(index).toString();


//     Перевірка, чи існує команда взагалі
    if (!db->teamExists(teamName)) {
        qDebug() << "Team does not exist.";
        return;
    }

    teamDialog=new TeamDialog(teamName);
    teamDialog->show();

}

