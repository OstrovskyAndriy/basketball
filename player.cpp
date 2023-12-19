#include "player.h"

Player::Player(const QString &firstName, const QString &lastName, int wins, int losses)
    : firstName(firstName), lastName(lastName), wins(wins), losses(losses) {}

QString Player::getFirstName() const {
    return firstName;
}

QString Player::getLastName() const {
    return lastName;
}

int Player::getWins() const {
    return wins;
}

int Player::getLosses() const {
    return losses;
}
