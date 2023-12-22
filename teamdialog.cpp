#include "teamdialog.h"
#include "ui_teamdialog.h"

TeamDialog::TeamDialog(const QString &teamName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamDialog)
{
    ui->setupUi(this);
    db=DBManager::getInstance();

    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->playersInfo->setSelectionMode(QAbstractItemView::NoSelection);
    ui->playersInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->teamInfo->setSelectionMode(QAbstractItemView::NoSelection);
    ui->teamInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playersInfo->verticalHeader()->setVisible(false);
    ui->teamInfo->verticalHeader()->setVisible(false);



    QSqlQueryModel* teamInfoModel = db->getTeamInfoModel(teamName);
    QSqlQueryModel* playersModel = db->getPlayersForTeamModel(teamName);

    // Відображення інформації про команду в QTableView
    ui->teamInfo->setModel(teamInfoModel);

    // Відображення інформації про гравців в QTableView
    ui->playersInfo->setModel(playersModel);

    for (int i = 0; i < playersModel->columnCount(); ++i) {
        ui->playersInfo->setColumnWidth(i, (ui->playersInfo->width()-5) / playersModel->columnCount());
    }

}

TeamDialog::~TeamDialog()
{
    delete ui;
}
