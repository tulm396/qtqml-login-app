#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "fileio.h"

#define AUTHEN_URL "http://localhost:8080/users/authenticate"
#define TOKEN_FILE "./access_token.bin"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);

    Q_INVOKABLE QString getUsername();
    Q_INVOKABLE void    userLogin(const QString& u, const QString& p); // u: username, p: password
    Q_INVOKABLE bool    isUserLoggedIn();

signals:
    void login(const int& flag, const QString& message);

public slots:
    void doAuthenticate(const QString& u, const QString& p);
    void onAuthenticateDone(QNetworkReply* reply);

private:
    QString m_jwtToken, m_username, m_password;
    bool    m_isLoggedIn;
};

#endif // MAINCONTROLLER_H
