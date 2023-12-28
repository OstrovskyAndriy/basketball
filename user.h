#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(const QString &username, const QString &password, bool isAdmin, const QString &email, const QString &phoneNumber);

    //
    QString getUsername() const;
    QString getPassword() const;
    bool isAdmin() const;
    QString getEmail() const;
    QString getPhoneNumber() const;

    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setAdmin(bool isAdmin);
    void setEmail(const QString &email);
    void setPhoneNumber(const QString &phoneNumber);

private:
    QString username;
    QString password;
    bool admin;
    QString email;
    QString phoneNumber;
};

#endif // USER_H
