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
#include <QVariantMap>
#include <QVariant>

#include "fileio.h"

#define AUTHEN_URL "http://localhost:8080/users/authenticate"
#define USER_PROFILE_URL "http://localhost:8080/users/profile"
#define TOKEN_FILE "./access_token.bin"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);

    Q_INVOKABLE QString getUsername();
    Q_INVOKABLE void    userLogin(const QString& u, const QString& p); // u: username, p: password
    Q_INVOKABLE bool    isUserLoggedIn();
    Q_INVOKABLE void    getUserProfile();
    Q_INVOKABLE void    userLogout();

signals:
    /// Emit when login have done
    /// flag: -1, message:
    /// flag:  0, message:
    /// flag:  1, message:
    void login(const int& flag, const QString& message);

    /// Emit when request user profile done
    /// flag: -1, message in data
    /// flag:  0, message in data
    /// flag:  1, message in data
    void getProfile(const int& flag, const QVariantMap& data);

    // Emit when logout have done
    void logout();

public slots:
    /// Authentication action
    void doAuthenticate(const QString& u, const QString& p);
    void onAuthenticateDone(QNetworkReply* reply);

    /// Users profile action
    void onGetUserProfileDone(QNetworkReply* reply);
    void doGetUserProfile();

private:
    QString m_jwtToken, m_username, m_password;
    bool    m_isLoggedIn;
};

#endif // MAINCONTROLLER_H
