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

bool DBManager::addTeam(const QString teamName, const std::vector<Player> &players)
{
    QSqlQuery query;

    // Вставка команди в таблицю Teams
    query.prepare("INSERT INTO Teams (team_name) VALUES (:teamName)");
    query.bindValue(":teamName", teamName);

    if (!query.exec()) {
        qDebug() << "Error inserting team into Teams table:" << query.lastError().text();
        return false;
    }

    // Отримання ідентифікатора вставленої команди
    query.prepare("SELECT team_id FROM Teams WHERE team_name = :teamName");
    query.bindValue(":teamName", teamName);

    int teamId = 0;
    if (query.exec() && query.next()) {
        teamId = query.value("team_id").toInt();
    } else {
        qDebug() << "Error retrieving team_id for the inserted team:" << query.lastError().text();
        return false;
    }

    // Вставка гравців в таблицю Players
    query.prepare("INSERT INTO Players (last_name, first_name, team_id, victories, defeats) "
                  "VALUES (:lastName, :firstName, :teamId, :victories, :defeats)");

    for (const Player &player : players) {
        query.bindValue(":lastName", player.getLastName());
        query.bindValue(":firstName", player.getFirstName());
        query.bindValue(":teamId", teamId);
        query.bindValue(":victories", player.getWins());
        query.bindValue(":defeats", player.getLosses());

        if (!query.exec()) {
            qDebug() << "Error inserting player into Players table:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

QStringList DBManager::getAllTeams()
{
    QStringList teams;
    QSqlQuery query("SELECT team_name FROM teams");

    if (query.exec()) {
        while (query.next()) {
            QString teamName = query.value("team_name").toString();
            teams << teamName;
        }
    } else {
        qDebug() << "Error retrieving teams from the database:" << query.lastError().text();
    }

    return teams;
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
                   "team_name VARCHAR(255));")
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
                        "team_id INTEGER,"
                        "victories INTEGER,"
                        "defeats INTEGER,"
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
