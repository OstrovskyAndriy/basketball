#include "dbmanager.h"
#include <stdexcept>  // Для std::runtime_error


DBManager* DBManager::instance = nullptr;

DBManager::DBManager(){
    this->connectToDataBase();
}

DBManager* DBManager::getInstance()
{
    if(instance == nullptr){
        instance = new DBManager();
    }
    return instance;
}


void DBManager::connectToDataBase()
{

    if(QFile("basketball.sqlite").exists()){
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

QSqlDatabase DBManager::getDB()
{
    return db;
}

bool DBManager::registerUser(const QString &username, const QString &password, bool isAdmin, const QString &email, const QString &phoneNumber) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, isAdmin, email, phone_number) "
                  "VALUES (:username, :password, :isAdmin, :email, :phone_number)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":isAdmin", isAdmin);
    query.bindValue(":email", email);
    query.bindValue(":phone_number", phoneNumber);

    if (query.exec()) {
        return true;  // Успішна реєстрація
    } else {
        qDebug() << "User registration failed:" << query.lastError().text();
        return false; // Невдача реєстрації
    }
}



bool DBManager::getUser(const QString &name, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    query.bindValue(":username", name);
    query.bindValue(":password", password);
    int userId = 0;
    bool isAdmin = false;

    if (query.exec() && query.next()) {
        // Користувач із вказаним логіном і паролем знайдений
        userId = query.value("user_id").toInt();
        isAdmin = query.value("isAdmin").toBool();
        qDebug() << "User found. User ID:" << userId;

        // Перевірка, чи користувач - адміністратор
        if (isAdmin) {
            qDebug() << "User is an admin.";
            return true;
        }
        else {
            qDebug() << "User is not an admin.";
        }
    }
    else {
        // Користувача із вказаним логіном і паролем не знайдено
        qDebug() << "User not found or invalid credentials.";
        throw std::runtime_error("User not found or invalid credentials.");  // Виняток
    }

    return false;
}

bool DBManager::addTeam(const QString teamName, const std::vector<Player> &players, int wins, int loses)
{
    QSqlQuery query;

    // Вставка команди в таблицю teams
    query.prepare("INSERT INTO teams (team_name, victories, defeats) VALUES (:teamName, :wins, :loses);");
    query.bindValue(":teamName", teamName);
    query.bindValue(":wins", wins);
    query.bindValue(":loses", loses);

    if (!query.exec()) {
        qDebug() << "Error adding team to the database:" << query.lastError().text();
        return false;
    }

    // Отримання ідентифікатора вставленої команди
    int teamId = query.lastInsertId().toInt();

    // Вставка гравців в таблицю players
    for (const Player &player : players) {
        addPlayer(player, teamId);
    }

    return true;
}

void DBManager::addPlayer(const Player &player, int teamId)
{
    QSqlQuery query;

    // Вставка гравця в таблицю players
    query.prepare("INSERT INTO players (first_name, last_name, height, team_id) "
                  "VALUES (:firstName, :lastName, :height, :teamId);");
    query.bindValue(":firstName", player.getFirstName());
    query.bindValue(":lastName", player.getLastName());
    query.bindValue(":height", player.getHeight());
    query.bindValue(":teamId", teamId);

    if (!query.exec()) {
        qDebug() << "Error adding player to the database:" << query.lastError().text();
        qDebug()<<query.lastQuery();
    }
}

QMap<int, QString> DBManager::getAllTeams()
{
    QMap<int, QString> teamsMap;
    QSqlQuery query("SELECT team_id, team_name FROM teams");

    if (query.exec()) {
        while (query.next()) {
            int teamId = query.value("team_id").toInt();
            QString teamName = query.value("team_name").toString();
            teamsMap.insert(teamId, teamName);
        }
    } else {
        qDebug() << "Error retrieving teams from the database:" << query.lastError().text();
    }

    return teamsMap;
}

bool DBManager::addGame(int team1Id, int team2Id, const QString &result, const QDate &gameDate, const QString &location) const
{
    QSqlQuery query;
    query.prepare("INSERT INTO games (date_played, team1_id, team2_id, score, location) "
                  "VALUES (:datePlayed, :team1Id, :team2Id, :score, :location)");
    query.bindValue(":datePlayed", gameDate.toString("yyyy-MM-dd"));
    query.bindValue(":team1Id", team1Id);
    query.bindValue(":team2Id", team2Id);
    query.bindValue(":score", result);
    query.bindValue(":location", location);

    if (!query.exec()) {
        qDebug() << "Error adding game:" << query.lastError().text();
        return false;
    }

    // Отримання інформації про результат гри
    QStringList scoreParts = result.split(":");
    int team1Score = scoreParts[0].toInt();
    int team2Score = scoreParts[1].toInt();

    // Оновлення статистики команд
    updateTeamStats(team1Id, team1Score > team2Score, team1Score < team2Score);
    updateTeamStats(team2Id, team2Score > team1Score, team2Score < team1Score);


    return true;
}

//функція для оновлення статистики виграшів/програшів для команди
void DBManager::updateTeamStats(int teamId, bool isVictorious, bool isDefeated) const
{
    QSqlQuery query;

    if (isVictorious) {
        query.prepare("UPDATE teams SET victories = victories + 1 WHERE team_id = :teamId");
    } else if (isDefeated) {
        query.prepare("UPDATE teams SET defeats = defeats + 1 WHERE team_id = :teamId");
    } else {
        return;  // Невідомий стан гри
    }

    query.bindValue(":teamId", teamId);

    if (!query.exec()) {
        qDebug() << "Error updating team stats:" << query.lastError().text();
    }
}

QSqlQueryModel* DBManager::getGameResultsModel(const QString& teamNameFilter) const
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString queryStr = "SELECT t1.team_name AS team1, g.score, t2.team_name AS team2, g.date_played, g.location "
                       "FROM games g "
                       "JOIN teams t1 ON g.team1_id = t1.team_id "
                       "JOIN teams t2 ON g.team2_id = t2.team_id";

    if (!teamNameFilter.isEmpty()) {
        queryStr += " WHERE t1.team_name = :teamName OR t2.team_name = :teamName";
    }

    QSqlQuery query;
    query.prepare(queryStr);

    if (!teamNameFilter.isEmpty()) {
        query.bindValue(":teamName", teamNameFilter);
    }

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return nullptr;  // Повертаємо nullptr в разі помилки виконання запиту
    }

    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error retrieving game results:" << model->lastError().text();
        return nullptr;  // Повертаємо nullptr в разі помилки отримання результатів запиту
    }

    return model;
}

bool DBManager::teamExists(const QString& teamName)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM teams WHERE team_name = :teamName");
    query.bindValue(":teamName", teamName);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    } else {
        qDebug() << "Error checking team existence:" << query.lastError().text();
        return false;
    }
}


QSqlQueryModel* DBManager::getTeamInfoModel(const QString& teamName)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM teams WHERE team_name = :teamName");
    query.bindValue(":teamName", teamName);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Error retrieving team information:" << query.lastError().text();
    }

    return model;
}

QSqlQueryModel* DBManager::getPlayersForTeamModel(const QString& teamName)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM players WHERE team_id IN (SELECT team_id FROM teams WHERE team_name = :teamName)");
    query.bindValue(":teamName", teamName);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Error retrieving players for team:" << query.lastError().text();
    }

    return model;
}







bool DBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалось відновити базу даних";
        return false;
    }
}


bool DBManager::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("basketball.sqlite");
    if(db.open()){
        return true;
    } else
        return false;
}


void DBManager::closeDataBase()
{
    db.close();
}

bool DBManager::createTables()
{
    QSqlQuery query;

    if(!query.exec("CREATE TABLE teams ("
                   "team_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "team_name VARCHAR(255),"
                   "victories INTEGER,"
                   "defeats INTEGER);")
            ||
            !query.exec("CREATE TABLE games ("
                        "game_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "date_played DATE,"
                        "team1_id INTEGER,"
                        "team2_id INTEGER,"
                        "score VARCHAR(10),"
                        "location VARCHAR(255),"
                        "FOREIGN KEY (team1_id) REFERENCES Teams(team_id),"
                        "FOREIGN KEY (team2_id) REFERENCES Teams(team_id));")
            ||
            !query.exec("CREATE TABLE players ("
                        "player_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "last_name VARCHAR(255),"
                        "first_name VARCHAR(255),"
                        "height INEGER,"
                        "team_id INTEGER,"
                        "FOREIGN KEY (team_id) REFERENCES Teams(team_id));")
            ||
            !query.exec("CREATE TABLE users ("
                        "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "username VARCHAR(255) UNIQUE,"
                        "password VARCHAR(255),"
                        "isAdmin BOLEAN,"
                        "email VARCHAR(255),"
                        "phone_number VARCHAR(20));"))
    {
        qDebug()<<"error creating table";
        qDebug() << query.lastError().text();
        return false;
    }

    // Вставка адміна
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Users (username, password, isAdmin, email, phone_number) "
                        "VALUES (:username, :password, :isAdmin, :email, :phone_number)");

    // Передача значень параметрів
    insertQuery.bindValue(":username", "admin");
    insertQuery.bindValue(":password", "admin");
    insertQuery.bindValue(":isAdmin", 1);
    insertQuery.bindValue(":email", "admin@gmail.com");
    insertQuery.bindValue(":phone_number", "0972345647");

    // Виконання SQL-запиту на вставку
    if (insertQuery.exec()) {
        qDebug() << "User inserted successfully.";
    } else {
        qDebug() << "Error inserting user:" << insertQuery.lastError().text();
    }

    return true;
}
