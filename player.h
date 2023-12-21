#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
public:
    Player(const QString &firstName, const QString &lastName,int height);

    QString getFirstName() const;
    QString getLastName() const;
    int getHeight() const;

private:
    QString firstName;
    QString lastName;

    int heigth;
};

#endif // PLAYER_H
