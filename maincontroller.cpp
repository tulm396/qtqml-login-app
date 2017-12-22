#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    m_isLoggedIn = false;
    m_jwtToken = "";
    m_username = "";
    m_password = "";

    // Read access token
    m_jwtToken = FileIO::readTokenFromFile(QString(TOKEN_FILE));
}

QString MainController::getUsername()
{
    return QString("tulm");
}

void MainController::userLogin(const QString& u, const QString& p)
{
    if (u.isNull() || p.isNull() || p.isEmpty() || u.isEmpty())
    {
        return;
    }
    doAuthenticate(u, p);
}

bool MainController::isUserLoggedIn()
{
    if (this->m_jwtToken.isEmpty())
        return false;
    return true;
}

// SLOTS: authenticating
void MainController::doAuthenticate(const QString &u, const QString &p)
{
    // Encrypting password before request
    m_username = u;
    m_password = QString(QCryptographicHash::hash(p.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    // Build JSON request body
    QJsonObject bodyJsonObj;
    bodyJsonObj.insert("username", u);
    bodyJsonObj.insert("password", m_password);
    QJsonDocument bodyJsonDoc(bodyJsonObj);

    // Building request
    QNetworkRequest request;
    request.setUrl(QUrl(AUTHEN_URL));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *restClient = new QNetworkAccessManager(this);
    connect(restClient, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthenticateDone(QNetworkReply*)), Qt::UniqueConnection);
    restClient->post(request, bodyJsonDoc.toJson());
}

// SLOTS: when authenticate done
void MainController::onAuthenticateDone(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // Cannot error to service api
    if (!(statusCode.isValid()))
    {
        emit login(-1, "Cannot connect to server");
        reply->deleteLater();
        return;
    }

    if(statusCode.isValid() && statusCode.value<int>() == 400)
    {
        emit login(0, "Login fail");
    }
    else if(statusCode.value<int>() == 200)
    {
        QByteArray resData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(resData);

        /// Write access token to file
        /// When run app later, it will be check
        this->m_jwtToken = jsonDoc.object()["token"].toString();
        FileIO::writeTokenToFile(QString(TOKEN_FILE), this->m_jwtToken);

        emit login(1, "Login succeed");
    }
    reply->deleteLater();
}

void MainController::getUserProfile()
{
    doGetUserProfile();
}

void MainController::userLogout()
{
    FileIO::deleteTokenFile(TOKEN_FILE);
    this->m_jwtToken.clear();
    emit logout();
}

void MainController::doGetUserProfile()
{
    QNetworkRequest request;
    request.setUrl(QUrl(USER_PROFILE_URL));
    request.setRawHeader("Authorization", this->m_jwtToken.toLocal8Bit());

    QNetworkAccessManager *restClient = new QNetworkAccessManager(this);
    connect(restClient, SIGNAL(finished(QNetworkReply*)), this, SLOT(onGetUserProfileDone(QNetworkReply*)), Qt::UniqueConnection);
    restClient->get(request);
}

///
/// SLOTS: when get the profile of user have done
/// params: reply -> store information after request (statusCode or body of response)
///
void MainController::onGetUserProfileDone(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariantMap data;

    //! Connect to server fail
    //! If the status code is invalid then
    //! the client cannot find the server
    if (!(statusCode.isValid()))
    {
        //! code: -1, connect server failed
        data.insert("message", "Cannot connect to server");
        emit getProfile(-1, data);
        reply->deleteLater();
        return;
    }

    //! Connect to the server success and
    //! we can send some request to the server
    if(statusCode.isValid() && statusCode.value<int>() == 400)
    {
        /// Emit if request fail, request sent but
        /// verified fail or token is null
        /// code: 0
        data.clear();
        data.insert("message", "Verified fail or token is null");
        emit getProfile(0, data);
    }
    else if(statusCode.value<int>() == 200)
    {
        QByteArray resData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(resData);

        data.clear();
        data.insert("message", "Get user profile successfully");
        data.insert("username", jsonDoc.object()["username"].toString());
        data.insert("address", jsonDoc.object()["address"].toString());

        /// Emit when successfully get user profile
        /// code: 1
        emit getProfile(1, data);
    }
    //! Final: clean up memory to avoid memory leak
    reply->deleteLater();
}
