#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase> // бібліотека бази даних
#include <QDebug> //бібліотека для відладки програми
#include <QSqlQuery> // бібліотека для запиту до баз даних
#include <QtSql>
#include <player.h>
#include <vector>


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
    bool registerUser(const QString &username, const QString &password, bool isAdmin, const QString &email, const QString &phoneNumber);

    bool addTeam(const QString teamName, const std::vector<Player> &players);
    QMap<int, QString> getAllTeams();
    bool addGame(int team1Id, int team2Id, const QString &result, const QDate &gameDate, const QString &location)const;

};

#endif // DBMANAGER_H
