#ifndef RESULTSDIALOG_H
#define RESULTSDIALOG_H

#include <QDialog>
#include "addgamedialog.h"
#include <dbmanager.h>
#include <teamdialog.h>

namespace Ui {
class ResultsDialog;
}

class ResultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsDialog(bool isAdmin, QWidget *parent = nullptr);
    ~ResultsDialog();

private slots:

    void on_addGameButton_clicked();

    void on_getBackButton_clicked();

    void setTableModel();

    void on_teamsComboBox_currentTextChanged(const QString &arg1);

    void fillComboBoxes();

    void setModelSettings(QSqlQueryModel &model);

    void on_resultsTable_doubleClicked(const QModelIndex &index);

signals:
    void backToLogin();

private:
    Ui::ResultsDialog *ui;
    AddGameDialog *addGameDialog;
    TeamDialog* teamDialog;

    DBManager *db;

};

#endif // RESULTSDIALOG_H
