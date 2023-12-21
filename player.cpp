#include "player.h"

Player::Player(const QString &firstName, const QString &lastName, int height)
    : firstName(firstName), lastName(lastName), heigth(height) {}

QString Player::getFirstName() const {
    return firstName;
}

QString Player::getLastName() const {
    return lastName;
}

int Player::getHeight() const {
    return heigth;
}
