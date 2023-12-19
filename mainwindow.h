#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbmanager.h>
#include <resultsdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

    void on_password_returnPressed();

private:
    Ui::MainWindow *ui;

    DBManager *db;
    ResultsDialog* resultsDialog;
};
#endif // MAINWINDOW_H
