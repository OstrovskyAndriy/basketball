#include "user.h"

User::User()
{
}

User::User(const QString &username, const QString &password, bool isAdmin, const QString &email, const QString &phoneNumber)
    : username(username), password(password), admin(isAdmin), email(email), phoneNumber(phoneNumber)
{
}

QString User::getUsername() const
{
    return username;
}

QString User::getPassword() const
{
    return password;
}

bool User::isAdmin() const
{
    return admin;
}

QString User::getEmail() const
{
    return email;
}

QString User::getPhoneNumber() const
{
    return phoneNumber;
}

// Setters
void User::setUsername(const QString &username)
{
    this->username = username;
}

void User::setPassword(const QString &password)
{
    this->password = password;
}

void User::setAdmin(bool isAdmin)
{
    this->admin = isAdmin;
}

void User::setEmail(const QString &email)
{
    this->email = email;
}

void User::setPhoneNumber(const QString &phoneNumber)
{
    this->phoneNumber = phoneNumber;
}
