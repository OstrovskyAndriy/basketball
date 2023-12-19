#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
public:
    Player(const QString &firstName, const QString &lastName, int wins, int losses);

    QString getFirstName() const;
    QString getLastName() const;
    int getWins() const;
    int getLosses() const;

private:
    QString firstName;
    QString lastName;
    int wins;
    int losses;
};

#endif // PLAYER_H
