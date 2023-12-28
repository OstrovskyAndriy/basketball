#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QSqlDatabase> // бібліотека бази даних
#include <QDebug> //бібліотека для відладки програми
#include <QSqlQuery> // бібліотека для запиту до баз даних
#include <QtSql>
#include <player.h>
#include <vector>
#include <user.h>

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

    User getUser(const QString &email, const QString &password);


    bool registerUser(User& user);


    bool addTeam(const QString teamName, const std::vector<Player> &players, int wins, int loses);

    void addPlayer(const Player &player, int teamId);

    QMap<int, QString> getAllTeams();

    bool addGame(int team1Id, int team2Id, const QString &result, const QDate &gameDate, const QString &location)const;

    void updateTeamStats(int teamId, bool isVictorious, bool isDefeated) const;

    QSqlQueryModel* getGameResultsModel(const QString& teamNameFilter = "") const;

    bool teamExists(const QString& teamName);

    QSqlQueryModel* getTeamInfoModel(const QString& teamName);

    QSqlQueryModel* getPlayersForTeamModel(const QString& teamName);



};

#endif // DBMANAGER_H
