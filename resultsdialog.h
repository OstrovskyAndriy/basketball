#ifndef RESULTSDIALOG_H
#define RESULTSDIALOG_H

#include <QDialog>
#include "addgamedialog.h"
#include <dbmanager.h>

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

private:
    Ui::ResultsDialog *ui;
    AddGameDialog *addGameDialog;

    DBManager *db;

};

#endif // RESULTSDIALOG_H
