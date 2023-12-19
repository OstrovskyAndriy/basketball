#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase> // бібліотека бази даних
#include <QDebug> //бібліотека для відладки програми
#include <QSqlQuery> // бібліотека для запиту до баз даних
#include <QtSql>


class DBManager
{
    QSqlDatabase db;

    static DBManager* instance;

    DBManager();

    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();

public:
    static DBManager* getInstance();

    void connectToDataBase();
    QSqlDatabase getDB();

    bool getUser(const QString &name, const QString &password);
};

#endif // DBMANAGER_H
