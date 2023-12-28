#include "teamdialog.h"
#include "ui_teamdialog.h"

TeamDialog::TeamDialog(const QString &teamName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamDialog)
{
    ui->setupUi(this);
    db = DBManager::getInstance();

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

    // Встановлення назв для стовпців у teamInfo
    teamInfoModel->setHeaderData(0, Qt::Horizontal, "ID команди");
    teamInfoModel->setHeaderData(1, Qt::Horizontal, "Назва");
    teamInfoModel->setHeaderData(2, Qt::Horizontal, "Перевоги");
    teamInfoModel->setHeaderData(3, Qt::Horizontal, "Програші");

    // Відображення інформації про гравців команди в QTableView
    ui->playersInfo->setModel(playersModel);

    // Встановлення назв для стовпців у playersInfo
    playersModel->setHeaderData(0, Qt::Horizontal, "ID гравця");
    playersModel->setHeaderData(1, Qt::Horizontal, "Прізвище");
    playersModel->setHeaderData(2, Qt::Horizontal, "Ім'я");
    playersModel->setHeaderData(3, Qt::Horizontal, "Ріст");

    for (int i = 0; i < playersModel->columnCount(); ++i) {
        ui->playersInfo->setColumnWidth(i, (ui->playersInfo->width() - 5) / playersModel->columnCount());
    }
}


TeamDialog::~TeamDialog()
{
    delete ui;
}
